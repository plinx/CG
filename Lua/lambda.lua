function make_pair(arg1)
	return function(arg2)
		return function(func)
			return func(arg1)(arg2)
		end
	end
end

function first(a1)
	return function()
		return a1
	end
end

function second()
	return function(a2)
		return a2
	end
end

function add(a1)
	return function(a2)
		return a1 - a2
	end
end


function main()
	pair = make_pair(1)("str")
	print(pair(first))
	print(pair(second))
	num_pair = make_pair(1)(2)
	print(num_pair(add))
end

main()