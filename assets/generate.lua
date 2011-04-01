function generate(name, fmt, min, ...)
	baseline = [[
int p_%s(char* text, int* consumed){
	%s // declarations
	char* check = tokenize(text, consumed, "\x%s" "%s"%s);
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

a = a .. "\n" .. generate("bot_add", "", 0, nil)
a = a .. "\n" .. generate("bot_add_ct", "", 0, nil)
a = a .. "\n" .. generate("bot_add_t", "", 0, nil)
a = a .. "\n" .. generate("bot_count", "i", 1, "count")
a = a .. "\n" .. generate("bot_jointeam", "i", 1, "team")
a = a .. "\n" .. generate("bot_kill", "", 0, nil)
a = a .. "\n" .. generate("bot_prefix", "s", 1, "prefix")
a = a .. "\n" .. generate("bot_remove", "", 0, nil)
a = a .. "\n" .. generate("bot_remove_all", "", 0, nil)
a = a .. "\n" .. generate("bot_remove_ct", "", 0, nil)
a = a .. "\n" .. generate("bot_remove_t", "", 0, nil)
a = a .. "\n" .. generate("bot_skill", "i", 1, "skill")
a = a .. "\n" .. generate("bot_weapons", "i", 1, "weapons")

a = a .. "\n" .. generate("effect", "siiiiiii", 8, "effect", "x", "y", "p1", "p2", "r", "g", "b")
a = a .. "\n" .. generate("equip", "ii", 2, "player", "weapon")
a = a .. "\n" .. generate("explosion", "iiiii", 5, "x", "y", "size", "damage", "source")
a = a .. "\n" .. generate("flashplayer", "ii", 2, "player", "intensity")
a = a .. "\n" .. generate("flashposition", "iii", 3, "x", "y", "intensity")
a = a .. "\n" .. generate("hudtxt", "isiii", 5, "id", "txt", "x", "y", "align")
a = a .. "\n" .. generate("hudtxt2", "iisiii", 6, "player", "id", "txt", "x", "y", "align")
a = a .. "\n" .. generate("hudtxtalphafade", "iiii", 4, "player", "id", "duration", "alpha")
a = a .. "\n" .. generate("hudtxtcolorfade", "iiiiii", 6, "player", "id", "duration", "red", "green", "blue")
a = a .. "\n" .. generate("hudtxtmove", "iiiii", 5, "player", "id", "duration", "x", "y")
a = a .. "\n" .. generate("items", "", 0, nil)
a = a .. "\n" .. generate("kick", "ss", 2, "player", "reason")
a = a .. "\n" .. generate("killobject", "i", 1, "object")
a = a .. "\n" .. generate("killplayer", "i", 1, "player")
a = a .. "\n" .. generate("listbans", "", 0, nil)
a = a .. "\n" .. generate("listplayers", "", 0, nil)
a = a .. "\n" .. generate("logaddress_add", "i", 1, "address")
a = a .. "\n" .. generate("logaddress_remove", "i", 1, "address")
a = a .. "\n" .. generate("logaddress_removeall", "", 0, nil)
a = a .. "\n" .. generate("lua", "s", 1, "script")
a = a .. "\n" .. generate("luareset", "", 0, nil)
a = a .. "\n" .. generate("makect", "s", 1, "player")
a = a .. "\n" .. generate("makespec", "s", 1, "player")
a = a .. "\n" .. generate("maket", "s", 1, "player")
a = a .. "\n" .. generate("map", "s", 1, "map")
a = a .. "\n" .. generate("maps", "", 0, nil)
a = a .. "\n" .. generate("mp_antispeeder", "i", 1, "antispeeder")
a = a .. "\n" .. generate("mp_autogamemode", "i", 1, "autogamemode")
a = a .. "\n" .. generate("mp_autoteambalance", "i", 1, "balance")
a = a .. "\n" .. generate("mp_building_health", "si", 2, "building", "price")
a = a .. "\n" .. generate("mp_building_limit", "si", 2, "building", "limit")
a = a .. "\n" .. generate("mp_building_price", "si", 2, "building", "price")
a = a .. "\n" .. generate("mp_buytime", "i", 1, "time")
a = a .. "\n" .. generate("mp_c4timer", "i", 1, "time")
a = a .. "\n" .. generate("mp_curtailedexplosions", "i", 1, "curtailed")
a = a .. "\n" .. generate("mp_damagefactor", "i", 1, "factor")
a = a .. "\n" .. generate("mp_deathdrop", "i", 1, "drop")
a = a .. "\n" .. generate("mp_dispenser_health", "i", 1, "health")
a = a .. "\n" .. generate("mp_dispenser_money", "i", 1, "money")
a = a .. "\n" .. generate("mp_dmspawnmoney", "i", 1, "money")
a = a .. "\n" .. generate("mp_dropgrenades", "i", 1, "drop")
a = a .. "\n" .. generate("mp_floodprot", "i", 1, "flood")
a = a .. "\n" .. generate("mp_freezetime", "i", 1, "time")
a = a .. "\n" .. generate("mp_grenaderebuy", "i", 1, "allowed")
a = a .. "\n" .. generate("mp_hostagepenalty", "i", 1, "kills")
a = a .. "\n" .. generate("mp_idleaction", "i", 1, "action")
a = a .. "\n" .. generate("mp_idlekick", "i", 1, "idle")
a = a .. "\n" .. generate("mp_idletime", "i", 1, "time")
a = a .. "\n" .. generate("mp_infammo", "i", 1, "infinite")
a = a .. "\n" .. generate("mp_kevlar", "i", 1, "percent")
a = a .. "\n" .. generate("mp_kickpercent", "i", 1, "percent")
a = a .. "\n" .. generate("mp_killbuildingmoney", "i", 1, "money")
a = a .. "\n" .. generate("mp_killbuildings", "i", 1, "kill")
a = a .. "\n" .. generate("mp_killinfo", "i", 1, "info")
a = a .. "\n" .. generate("mp_killteambuildings", "i", 1, "mode")
a = a .. "\n" .. generate("mp_lagcompensation", "i", 1, "max")
a = a .. "\n" .. generate("mp_localrconoutput", "i", 1, "output")
a = a .. "\n" .. generate("mp_luamap", "i", 1, "use")
a = a .. "\n" .. generate("mp_luaserver", "s", 1, "file")
a = a .. "\n" .. generate("mp_mapgoalscore", "i", 1, "score")
a = a .. "\n" .. generate("mp_mapvoteratio", "i", 1, "percent")
a = a .. "\n" .. generate("mp_maxclientsip", "i", 1, "clients")
a = a .. "\n" .. generate("mp_maxrconfails", "i", 1, "max")
a = a .. "\n" .. generate("mp_natholepunching", "i", 1, "allow")
a = a .. "\n" .. generate("mp_pinglimit", "i", 1, "limit")
a = a .. "\n" .. generate("mp_postspawn", "i", 1, "time")
a = a .. "\n" .. generate("mp_radar", "i", 1, "radar")
a = a .. "\n" .. generate("mp_randomspawn", "i", 1, "random")
a = a .. "\n" .. generate("mp_reservations", "s", 1, "reservations")
a = a .. "\n" .. generate("mp_respawndelay", "i", 1, "delay")
a = a .. "\n" .. generate("mp_roundlimit", "i", 1, "rounds")
a = a .. "\n" .. generate("mp_roundtime", "i", 1, "time")
a = a .. "\n" .. generate("mp_startmoney", "i", 1, "money")
a = a .. "\n" .. generate("mp_supply_items", "s", 1, "itemlist")
a = a .. "\n" .. generate("mp_teamkillpenalty", "i", 1, "kills")
a = a .. "\n" .. generate("mp_teleportreload", "i", 1, "reload")
a = a .. "\n" .. generate("mp_tempbantime", "i", 1, "time")
a = a .. "\n" .. generate("mp_timelimit", "i", 1, "time")
a = a .. "\n" .. generate("mp_tkpunish", "i", 1, "kill")
a = a .. "\n" .. generate("mp_trace", "i", 1, "accuracy")
a = a .. "\n" .. generate("mp_turretdamage", "i", 1, "damage")
a = a .. "\n" .. generate("mp_unbuildable", "s", 1, "buildings")
a = a .. "\n" .. generate("mp_unbuyable", "s", 1, "unbuyable")
a = a .. "\n" .. generate("mp_vulnerablehostages", "i", 1, "vulnerable")
a = a .. "\n" .. generate("mp_winlimit", "i", 1, "wins")
a = a .. "\n" .. generate("mp_wpndmg", "si", 2, "name", "damage")
a = a .. "\n" .. generate("mp_wpndmg_z1", "si", 2, "name", "damage")
a = a .. "\n" .. generate("mp_wpndmg_z2", "si", 2, "name", "damage")
a = a .. "\n" .. generate("mp_zombiedmg", "i", 1, "percentage")
a = a .. "\n" .. generate("mp_zombiekillequip", "i", 1, "weapon")
a = a .. "\n" .. generate("mp_zombiekillscore", "i", 1, "kill")
a = a .. "\n" .. generate("mp_zombierecover", "i", 1, "recover")
a = a .. "\n" .. generate("mp_zombiespeedmod", "i", 1, "speedmod")
a = a .. "\n" .. generate("msg", "s", 1, "message")
a = a .. "\n" .. generate("rcon", "s", 1, "commands")
a = a .. "\n" .. generate("rcon_password", "s", 1, "password")
a = a .. "\n" .. generate("rcon_pw", "s", 1, "password")
a = a .. "\n" .. generate("removeitem", "i", 1, "item")
a = a .. "\n" .. generate("reroute", "is", 2, "player", "address")
a = a .. "\n" .. generate("restart", "i", 1, "delay")
a = a .. "\n" .. generate("restartround", "i", 1, "delay")
a = a .. "\n" .. generate("setarmor", "ii", 2, "player", "armor")
a = a .. "\n" .. generate("setdeaths", "ii", 2, "player", "deaths")
a = a .. "\n" .. generate("sethealth", "ii", 2, "player", "health")
a = a .. "\n" .. generate("setmaxhealth", "ii", 2, "player", "maxhealth")
a = a .. "\n" .. generate("setmoney", "ii", 2, "player", "money")
a = a .. "\n" .. generate("setname", "is", 2, "player", "name")
a = a .. "\n" .. generate("setpos", "iii", 3, "player", "x", "y")
a = a .. "\n" .. generate("setscore", "ii", 2, "player", "score")
a = a .. "\n" .. generate("setweapon", "ii", 2, "player", "weapon")
a = a .. "\n" .. generate("shake", "ii", 2, "player", "power")
a = a .. "\n" .. generate("slap", "s", 1, "player")
a = a .. "\n" .. generate("spawnitem", "iii", 3, "item", "x", "y")
a = a .. "\n" .. generate("spawnnpc", "iiii", 4, "type", "x", "y", "rot")
a = a .. "\n" .. generate("spawnobject", "iiiiiii", 7, "type", "x", "y", "rot", "mode", "team", "player")
a = a .. "\n" .. generate("spawnplayer", "iii", 3, "player", "x", "y")
a = a .. "\n" .. generate("speedmod", "ii", 2, "player", "speedmod")
a = a .. "\n" .. generate("strip", "ii", 2, "player", "weapon")
a = a .. "\n" .. generate("sv_fow", "i", 1, "fow")
a = a .. "\n" .. generate("sv_friendlyfire", "i", 1, "FF")
a = a .. "\n" .. generate("sv_gamemode", "i", 1, "mode")
a = a .. "\n" .. generate("sv_gm", "i", 1, "mode")
a = a .. "\n" .. generate("sv_hostport", "i", 1, "port")
a = a .. "\n" .. generate("sv_lan", "i", 1, "lan")
a = a .. "\n" .. generate("sv_map", "s", 1, "map")
a = a .. "\n" .. generate("sv_maptransfer", "i", 1, "transfer")
a = a .. "\n" .. generate("sv_maxplayers", "i", 1, "players")
a = a .. "\n" .. generate("sv_msg", "s", 1, "message")
a = a .. "\n" .. generate("sv_msg2", "is", 2, "player", "message")
a = a .. "\n" .. generate("sv_name", "s", 1, "name")
a = a .. "\n" .. generate("sv_password", "s", 1, "password")
a = a .. "\n" .. generate("sv_rcon", "s", 1, "rcon")
a = a .. "\n" .. generate("sv_restart", "i", 1, "delay")
a = a .. "\n" .. generate("sv_restartround", "i", 1, "delay")
a = a .. "\n" .. generate("sv_sound", "s", 1, "soundfile")
a = a .. "\n" .. generate("sv_sound2", "is", 2, "player", "soundfile")
a = a .. "\n" .. generate("sv_specmode", "i", 1, "mode")
a = a .. "\n" .. generate("sv_spraytransfer", "i", 1, "spray")
a = a .. "\n" .. generate("sv_usgnonly", "i", 1, "usgn")
a = a .. "\n" .. generate("transfer_speed", "i", 1, "speed")
a = a .. "\n" .. generate("trigger", "s", 1, "trigger")
a = a .. "\n" .. generate("unban", "s", 1, "banmask")
a = a .. "\n" .. generate("unbanall", "", 0, nil)
a = a .. "\n" .. generate("usgn_addserver", "", 0, nil)
a = a .. "\n" .. generate("usgn_info", "", 0, nil)

print(a)
f = io.open("partial_parse.part", "w")
f:write(a)
f:close()

