Server = { socket, host, port, conn}

function Server:init()
	self.socket = require("socket")
	self.host = "localhost"
	self.port = "12345"

	self.conn = assert(socket.bind(self.host, self.port, 1024))
	self.conn:settimeout(0)
end

function Server:run()
	local client

	while true do
		local conn = self.conn:accept()
		if conn then 
			client = conn
			print("Client connect.")
		end

        local recv_buf = self:get_message(client)
        -- if recv_buf == "closed" then
       	if recv_buf ~= nil then
       		if recv_buf ~= "closed" then
        		print("Receive request : " .. recv_buf)
        	    local send_buf = self:json_decode(recv_buf)
        	    print("Send result : " .. send_buf)
        	    assert(client:send("Get result : " .. send_buf .. "\n"))
        	else
        		break
        	end
        end
	end
	print("Client disconnected.")
	client:close()
end

function Server:get_message(client)
	local recvt, sendt, status = self.socket.select({client}, nil, 1)
	if #recvt > 0 then
        local receive, receive_status = client:receive()
        if receive_status ~= "closed" then
            if receive then
            	return receive
            end
        else
        	return "closed"
        end
    end
end

function Server:json_decode(input)
	local values = {}
	local head, tail
	local cnt = 1
	local ocnt = 1

	head, tail = input:sub(1, #input):find("\"")
	while true do
		_, tail = input:sub(head + 1, #input):find("\"")
		if tail == nil then
			break
		end
		tmp = input:sub(head + 1, head + tail - 1)
		head = head + tail
		cnt = cnt + 1
		if cnt == 2 then
			values[ocnt] = tmp
			ocnt = ocnt + 1
			cnt = 0
		end
	end

	return self:execute(values)
end

function Server:execute(values)
	if values[1] == "add" then
		return tonumber(values[3]) + tonumber(values[5])
	elseif values[1] == "sub" then
		return tonumber(values[3]) - tonumber(values[5])
	else
		return "No this command => Usage : <add | sub> value1 value2"
	end
end

function main()
	Server:init()
	Server:run()
end


main()