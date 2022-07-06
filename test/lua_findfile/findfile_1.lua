files = merger.findfile("./*")

content = ""

for i, name in ipairs(files) do
    content = content .. name .. "\n"
end

merger.finialize(0, content)
