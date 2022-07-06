local pattern = ""
local matcher = ""
local flag_exe_arg = 0;
local command = ""

for i,v in ipairs(arg) do
    if flag_exe_arg == 0 then
        if string.find(v, "--pattern=") ~= nil then
            pattern = string.sub(v, 11)
        end
        if string.find(v, "--matcher=") ~= nil then
            matcher = string.sub(v, 11)
        end
        if v == "--" then
            flag_exe_arg = 1
        end
    else
        if command == "" then
            command = v
        else
            command = command .. " " .. v
        end
    end
end

if pattern == "" then
    io.write("missing argument --pattern")
    return
end

if matcher == "" then
    io.write("missing argument --matcher")
    return
end

os.execute(command)

local function read_file(path)
    local file = io.open(path, "rb") -- r read mode and b binary mode
    if not file then return nil end
    local content = file:read "*a" -- *a or *all reads the whole file
    file:close()
    return content
end

function hex_dump(buf)
   for i=1,math.ceil(#buf/16) * 16 do
      if (i-1) % 16 == 0 then io.write(string.format('%08X  ', i-1)) end
      io.write( i > #buf and '   ' or string.format('%02X ', buf:byte(i)) )
      if i %  8 == 0 then io.write(' ') end
      if i % 16 == 0 then io.write( buf:sub(i-16+1, i):gsub('%c','.'), '\n' ) end
   end
end

pattern_data = read_file(pattern)
matcher_data = read_file(matcher)

if pattern_data == matcher_data then
    return
end

io.write("except:\n")
hex_dump(pattern_data)
io.write("got:\n")
hex_dump(matcher_data)

os.exit(-1)
