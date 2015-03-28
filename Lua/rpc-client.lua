Client = { socket, host, port, conn }

function Client:init()
	self.socket = require("socket")
	self.host = "localhost"
	self.port = "12345"

	self.conn = assert(self.socket.connect(self.host, self.port))
	self.conn:settimeout(5)
end

function Client:run()
	local write = io.write
	local read = io.read

	local input, sendbuf
	while true do
		write("~$ ")
		input = read()
		if #input > 0 then
			if input == "quit" or input == "exit" then
				break
			end

			local send_buf = self:json_encode(input)
			if send_buf ~= nil then
				print("Send message to server : \n" .. send_buf)
				assert(self.conn:send(send_buf .. "\n"))
			end

			local recv_buf = self:get_result()
			if recv_buf == "closed" then
				break
			elseif recv_buf ~= nil then
				print(recv_buf)
			end
		end
	end
	print("Server disconnected.")
	self.conn:close()
end

function Client:get_result()
	local recvt, sendt, status = self.socket.select({self.conn}, nil, 1)
	if #recvt > 0 then
        local response, receive_status = self.conn:receive()
        if receive_status ~= "closed" then
            if response then
                return response
            else
            	return "No response"
            end
        else
        	return "closed"
        end
    end
end

function Client:json_encode(input)
	local json_string = ""
	if #input > 5 and input:sub(4, 4) == " " then
		json_string = "{ \"" .. input:sub(1, 3) .. "\" : [ " ..
		"\"value1\" : \""
		_, div_index = input:sub(5, #input):find(" ")
		div_index = div_index + 4
		if (div_index ~= #input) then
			json_string = json_string .. input:sub(5, div_index - 1) 
				.. "\", \"value2\" : \""
			json_string = json_string .. input:sub(div_index + 1, #input) 
				.. "\" ] }"
				return json_string
		else
			print("No enough input values")
				return nil
		end
	else
		print("JSON Encode Error.")
		return nil
	end
end

function main()
	Client:init()
	Client:run()
end

main()