addhook("join", "lol")
function lol(id)
	print("Hello ",id)
end

addhook("leave", "lol2")
function lol2(id, r)
	print("Goodbye ", id, r)
end

addhook("select", "lol3")
function lol3(id, wpn)
	msg2(id, "wpn", id, wpn)
end
