 

print("This is a Lua script!")

-- Naive recursive
function fib(n)
  local function inner(m)
    if m < 2 then
      return m
    end
    return inner(m-1) + inner(m-2)
  end
  return inner(n)
end

local num = 1
while num ~= 0 do
	num = io.read("*number")
	print("Your number is " .. fib(num))
end
