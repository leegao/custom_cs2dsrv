function generate(name, fmt, min, ...)
	baseline = [[
int p_%s(char* text, int* consumed){
	%s // declarations
	char* check = tokenize(text, consumed, "\%s" "%s"%s);
	if (!check) return 0;

	// %s_cmd(%s);

	return 1;
}
	]]
	local args = {...}
	local declaration = ""
	local parameter = ""
	local identifiers = {}
	for i=1,#fmt do
		local t = string.char(fmt:byte(i))
		local identifier = args[i]
		if not identifier then identifier = "_"..i end
		if type(identifier) == "table" then
			identifier = identifier[1]
		end

		if t == "s" then
			declaration = declaration .. "char* "..identifier
		elseif t == "i" then
			declaration = declaration .. "int "..identifier
		elseif t == "f" then
			declaration = declaration .. "float "..identifier
		else
			declaration = declaration .. "void* "..identifier
		end
		if type(args[i]) == "table" then
			declaration = declaration .. " = "
			if t == "s" then declaration = declaration .. '"'..args[i][2]..'"'
			else declaration = declaration .. args[i][2] end
		end
		declaration = declaration .. "; "
		parameter = parameter .. ", &"..identifier
		table.insert(identifiers, identifier)
	end
	identifiers = table.concat(identifiers, ", ")
	return baseline:format(name, declaration, min, fmt, parameter, name, identifiers)
end

a = ""
a = a .. "\n" .. generate("banip", "si", 1, "ip", {"duration",-1})
a = a .. "\n" .. generate("banname", "si", 1, "name", {"duration",-1})
a = a .. "\n" .. generate("bans", "", 0)
a = a .. "\n" .. generate("banusgn", "ii", 1, "usgn", {"duration",-1})
a = a .. "\n" .. generate("changelevel", "s", 1, "map")
a = a .. "\n" .. generate("changemap", "s", 1, "map")
a = a .. "\n" .. generate("customkill", "isi", 3, "killer", "weapon", "victim")
a = a .. "\n" .. generate("deathslap", "s", 1, "player")

print(a)

