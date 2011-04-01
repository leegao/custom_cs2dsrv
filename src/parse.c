/*
 * parse.c
 *
 *  Created on: Mar 29, 2011
 *      Author: leegao
 */

#include "parse.h"



// p_xxx functions starts here.


int p_banip(char* text, int* consumed){
	char* ip; int duration = -1;  // declarations
	char* check = tokenize(text, consumed, "\x1" "si", &ip, &duration);
	if (!check) return 0;

	// banip_cmd(ip, duration);

	return 1;
}

int p_banname(char* text, int* consumed){
	char* name; int duration = -1;  // declarations
	char* check = tokenize(text, consumed, "\x1" "si", &name, &duration);
	if (!check) return 0;

	// banname_cmd(name, duration);

	return 1;
}

int p_bans(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// bans_cmd();

	return 1;
}

int p_banusgn(char* text, int* consumed){
	int usgn; int duration = -1;  // declarations
	char* check = tokenize(text, consumed, "\x1" "ii", &usgn, &duration);
	if (!check) return 0;

	// banusgn_cmd(usgn, duration);

	return 1;
}

int p_changelevel(char* text, int* consumed){
	char* map;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &map);
	if (!check) return 0;

	// changelevel_cmd(map);

	return 1;
}

int p_changemap(char* text, int* consumed){
	char* map;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &map);
	if (!check) return 0;

	// changemap_cmd(map);

	return 1;
}

int p_customkill(char* text, int* consumed){
	int killer; char* weapon; int victim;  // declarations
	char* check = tokenize(text, consumed, "\x3" "isi", &killer, &weapon, &victim);
	if (!check) return 0;

	// customkill_cmd(killer, weapon, victim);

	return 1;
}

int p_deathslap(char* text, int* consumed){
	char* player;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &player);
	if (!check) return 0;

	// deathslap_cmd(player);

	return 1;
}

int p_bot_add(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// bot_add_cmd();

	return 1;
}

int p_bot_add_ct(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// bot_add_ct_cmd();

	return 1;
}

int p_bot_add_t(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// bot_add_t_cmd();

	return 1;
}

int p_bot_count(char* text, int* consumed){
	int count;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &count);
	if (!check) return 0;

	// bot_count_cmd(count);

	return 1;
}

int p_bot_jointeam(char* text, int* consumed){
	int team;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &team);
	if (!check) return 0;

	// bot_jointeam_cmd(team);

	return 1;
}

int p_bot_kill(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// bot_kill_cmd();

	return 1;
}

int p_bot_prefix(char* text, int* consumed){
	char* prefix;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &prefix);
	if (!check) return 0;

	// bot_prefix_cmd(prefix);

	return 1;
}

int p_bot_remove(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// bot_remove_cmd();

	return 1;
}

int p_bot_remove_all(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// bot_remove_all_cmd();

	return 1;
}

int p_bot_remove_ct(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// bot_remove_ct_cmd();

	return 1;
}

int p_bot_remove_t(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// bot_remove_t_cmd();

	return 1;
}

int p_bot_skill(char* text, int* consumed){
	int skill;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &skill);
	if (!check) return 0;

	// bot_skill_cmd(skill);

	return 1;
}

int p_bot_weapons(char* text, int* consumed){
	int weapons;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &weapons);
	if (!check) return 0;

	// bot_weapons_cmd(weapons);

	return 1;
}

int p_effect(char* text, int* consumed){
	char* effect; int x; int y; int p1; int p2; int r; int g; int b;  // declarations
	char* check = tokenize(text, consumed, "\x8" "siiiiiii", &effect, &x, &y, &p1, &p2, &r, &g, &b);
	if (!check) return 0;

	// effect_cmd(effect, x, y, p1, p2, r, g, b);

	return 1;
}

int p_equip(char* text, int* consumed){
	int player; int weapon;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &weapon);
	if (!check) return 0;

	// equip_cmd(player, weapon);

	return 1;
}

int p_explosion(char* text, int* consumed){
	int x; int y; int size; int damage; int source;  // declarations
	char* check = tokenize(text, consumed, "\x5" "iiiii", &x, &y, &size, &damage, &source);
	if (!check) return 0;

	// explosion_cmd(x, y, size, damage, source);

	return 1;
}

int p_flashplayer(char* text, int* consumed){
	int player; int intensity;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &intensity);
	if (!check) return 0;

	// flashplayer_cmd(player, intensity);

	return 1;
}

int p_flashposition(char* text, int* consumed){
	int x; int y; int intensity;  // declarations
	char* check = tokenize(text, consumed, "\x3" "iii", &x, &y, &intensity);
	if (!check) return 0;

	// flashposition_cmd(x, y, intensity);

	return 1;
}

int p_hudtxt(char* text, int* consumed){
	int id; char* txt; int x; int y; int align;  // declarations
	char* check = tokenize(text, consumed, "\x5" "isiii", &id, &txt, &x, &y, &align);
	if (!check) return 0;

	// hudtxt_cmd(id, txt, x, y, align);

	return 1;
}

int p_hudtxt2(char* text, int* consumed){
	int player; int id; char* txt; int x; int y; int align;  // declarations
	char* check = tokenize(text, consumed, "\x6" "iisiii", &player, &id, &txt, &x, &y, &align);
	if (!check) return 0;

	// hudtxt2_cmd(player, id, txt, x, y, align);

	return 1;
}

int p_hudtxtalphafade(char* text, int* consumed){
	int player; int id; int duration; int alpha;  // declarations
	char* check = tokenize(text, consumed, "\x4" "iiii", &player, &id, &duration, &alpha);
	if (!check) return 0;

	// hudtxtalphafade_cmd(player, id, duration, alpha);

	return 1;
}

int p_hudtxtcolorfade(char* text, int* consumed){
	int player; int id; int duration; int red; int green; int blue;  // declarations
	char* check = tokenize(text, consumed, "\x6" "iiiiii", &player, &id, &duration, &red, &green, &blue);
	if (!check) return 0;

	// hudtxtcolorfade_cmd(player, id, duration, red, green, blue);

	return 1;
}

int p_hudtxtmove(char* text, int* consumed){
	int player; int id; int duration; int x; int y;  // declarations
	char* check = tokenize(text, consumed, "\x5" "iiiii", &player, &id, &duration, &x, &y);
	if (!check) return 0;

	// hudtxtmove_cmd(player, id, duration, x, y);

	return 1;
}

int p_items(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// items_cmd();

	return 1;
}

int p_kick(char* text, int* consumed){
	char* player; char* reason;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ss", &player, &reason);
	if (!check) return 0;

	// kick_cmd(player, reason);

	return 1;
}

int p_killobject(char* text, int* consumed){
	int object;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &object);
	if (!check) return 0;

	// killobject_cmd(object);

	return 1;
}

int p_killplayer(char* text, int* consumed){
	int player;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &player);
	if (!check) return 0;

	// killplayer_cmd(player);

	return 1;
}

int p_listbans(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// listbans_cmd();

	return 1;
}

int p_listplayers(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// listplayers_cmd();

	return 1;
}

int p_logaddress_add(char* text, int* consumed){
	int address;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &address);
	if (!check) return 0;

	// logaddress_add_cmd(address);

	return 1;
}

int p_logaddress_remove(char* text, int* consumed){
	int address;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &address);
	if (!check) return 0;

	// logaddress_remove_cmd(address);

	return 1;
}

int p_logaddress_removeall(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// logaddress_removeall_cmd();

	return 1;
}

int p_lua(char* text, int* consumed){
	char* script;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &script);
	if (!check) return 0;

	// lua_cmd(script);

	return 1;
}

int p_luareset(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// luareset_cmd();

	return 1;
}

int p_makect(char* text, int* consumed){
	char* player;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &player);
	if (!check) return 0;

	// makect_cmd(player);

	return 1;
}

int p_makespec(char* text, int* consumed){
	char* player;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &player);
	if (!check) return 0;

	// makespec_cmd(player);

	return 1;
}

int p_maket(char* text, int* consumed){
	char* player;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &player);
	if (!check) return 0;

	// maket_cmd(player);

	return 1;
}

int p_map(char* text, int* consumed){
	char* map;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &map);
	if (!check) return 0;

	// map_cmd(map);

	return 1;
}

int p_maps(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// maps_cmd();

	return 1;
}

int p_mp_antispeeder(char* text, int* consumed){
	int antispeeder;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &antispeeder);
	if (!check) return 0;

	// mp_antispeeder_cmd(antispeeder);

	return 1;
}

int p_mp_autogamemode(char* text, int* consumed){
	int autogamemode;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &autogamemode);
	if (!check) return 0;

	// mp_autogamemode_cmd(autogamemode);

	return 1;
}

int p_mp_autoteambalance(char* text, int* consumed){
	int balance;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &balance);
	if (!check) return 0;

	// mp_autoteambalance_cmd(balance);

	return 1;
}

int p_mp_building_health(char* text, int* consumed){
	char* building; int price;  // declarations
	char* check = tokenize(text, consumed, "\x2" "si", &building, &price);
	if (!check) return 0;

	// mp_building_health_cmd(building, price);

	return 1;
}

int p_mp_building_limit(char* text, int* consumed){
	char* building; int limit;  // declarations
	char* check = tokenize(text, consumed, "\x2" "si", &building, &limit);
	if (!check) return 0;

	// mp_building_limit_cmd(building, limit);

	return 1;
}

int p_mp_building_price(char* text, int* consumed){
	char* building; int price;  // declarations
	char* check = tokenize(text, consumed, "\x2" "si", &building, &price);
	if (!check) return 0;

	// mp_building_price_cmd(building, price);

	return 1;
}

int p_mp_buytime(char* text, int* consumed){
	int time;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &time);
	if (!check) return 0;

	// mp_buytime_cmd(time);

	return 1;
}

int p_mp_c4timer(char* text, int* consumed){
	int time;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &time);
	if (!check) return 0;

	// mp_c4timer_cmd(time);

	return 1;
}

int p_mp_curtailedexplosions(char* text, int* consumed){
	int curtailed;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &curtailed);
	if (!check) return 0;

	// mp_curtailedexplosions_cmd(curtailed);

	return 1;
}

int p_mp_damagefactor(char* text, int* consumed){
	int factor;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &factor);
	if (!check) return 0;

	// mp_damagefactor_cmd(factor);

	return 1;
}

int p_mp_deathdrop(char* text, int* consumed){
	int drop;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &drop);
	if (!check) return 0;

	// mp_deathdrop_cmd(drop);

	return 1;
}

int p_mp_dispenser_health(char* text, int* consumed){
	int health;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &health);
	if (!check) return 0;

	// mp_dispenser_health_cmd(health);

	return 1;
}

int p_mp_dispenser_money(char* text, int* consumed){
	int money;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &money);
	if (!check) return 0;

	// mp_dispenser_money_cmd(money);

	return 1;
}

int p_mp_dmspawnmoney(char* text, int* consumed){
	int money;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &money);
	if (!check) return 0;

	// mp_dmspawnmoney_cmd(money);

	return 1;
}

int p_mp_dropgrenades(char* text, int* consumed){
	int drop;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &drop);
	if (!check) return 0;

	// mp_dropgrenades_cmd(drop);

	return 1;
}

int p_mp_floodprot(char* text, int* consumed){
	int flood;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &flood);
	if (!check) return 0;

	// mp_floodprot_cmd(flood);

	return 1;
}

int p_mp_freezetime(char* text, int* consumed){
	int time;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &time);
	if (!check) return 0;

	// mp_freezetime_cmd(time);

	return 1;
}

int p_mp_grenaderebuy(char* text, int* consumed){
	int allowed;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &allowed);
	if (!check) return 0;

	// mp_grenaderebuy_cmd(allowed);

	return 1;
}

int p_mp_hostagepenalty(char* text, int* consumed){
	int kills;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &kills);
	if (!check) return 0;

	// mp_hostagepenalty_cmd(kills);

	return 1;
}

int p_mp_idleaction(char* text, int* consumed){
	int action;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &action);
	if (!check) return 0;

	// mp_idleaction_cmd(action);

	return 1;
}

int p_mp_idlekick(char* text, int* consumed){
	int idle;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &idle);
	if (!check) return 0;

	// mp_idlekick_cmd(idle);

	return 1;
}

int p_mp_idletime(char* text, int* consumed){
	int time;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &time);
	if (!check) return 0;

	// mp_idletime_cmd(time);

	return 1;
}

int p_mp_infammo(char* text, int* consumed){
	int infinite;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &infinite);
	if (!check) return 0;

	// mp_infammo_cmd(infinite);

	return 1;
}

int p_mp_kevlar(char* text, int* consumed){
	int percent;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &percent);
	if (!check) return 0;

	// mp_kevlar_cmd(percent);

	return 1;
}

int p_mp_kickpercent(char* text, int* consumed){
	int percent;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &percent);
	if (!check) return 0;

	// mp_kickpercent_cmd(percent);

	return 1;
}

int p_mp_killbuildingmoney(char* text, int* consumed){
	int money;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &money);
	if (!check) return 0;

	// mp_killbuildingmoney_cmd(money);

	return 1;
}

int p_mp_killbuildings(char* text, int* consumed){
	int kill;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &kill);
	if (!check) return 0;

	// mp_killbuildings_cmd(kill);

	return 1;
}

int p_mp_killinfo(char* text, int* consumed){
	int info;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &info);
	if (!check) return 0;

	// mp_killinfo_cmd(info);

	return 1;
}

int p_mp_killteambuildings(char* text, int* consumed){
	int mode;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &mode);
	if (!check) return 0;

	// mp_killteambuildings_cmd(mode);

	return 1;
}

int p_mp_lagcompensation(char* text, int* consumed){
	int max;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &max);
	if (!check) return 0;

	// mp_lagcompensation_cmd(max);

	return 1;
}

int p_mp_localrconoutput(char* text, int* consumed){
	int output;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &output);
	if (!check) return 0;

	// mp_localrconoutput_cmd(output);

	return 1;
}

int p_mp_luamap(char* text, int* consumed){
	int use;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &use);
	if (!check) return 0;

	// mp_luamap_cmd(use);

	return 1;
}

int p_mp_luaserver(char* text, int* consumed){
	char* file;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &file);
	if (!check) return 0;

	// mp_luaserver_cmd(file);

	return 1;
}

int p_mp_mapgoalscore(char* text, int* consumed){
	int score;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &score);
	if (!check) return 0;

	// mp_mapgoalscore_cmd(score);

	return 1;
}

int p_mp_mapvoteratio(char* text, int* consumed){
	int percent;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &percent);
	if (!check) return 0;

	// mp_mapvoteratio_cmd(percent);

	return 1;
}

int p_mp_maxclientsip(char* text, int* consumed){
	int clients;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &clients);
	if (!check) return 0;

	// mp_maxclientsip_cmd(clients);

	return 1;
}

int p_mp_maxrconfails(char* text, int* consumed){
	int max;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &max);
	if (!check) return 0;

	// mp_maxrconfails_cmd(max);

	return 1;
}

int p_mp_natholepunching(char* text, int* consumed){
	int allow;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &allow);
	if (!check) return 0;

	// mp_natholepunching_cmd(allow);

	return 1;
}

int p_mp_pinglimit(char* text, int* consumed){
	int limit;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &limit);
	if (!check) return 0;

	// mp_pinglimit_cmd(limit);

	return 1;
}

int p_mp_postspawn(char* text, int* consumed){
	int time;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &time);
	if (!check) return 0;

	// mp_postspawn_cmd(time);

	return 1;
}

int p_mp_radar(char* text, int* consumed){
	int radar;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &radar);
	if (!check) return 0;

	// mp_radar_cmd(radar);

	return 1;
}

int p_mp_randomspawn(char* text, int* consumed){
	int random;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &random);
	if (!check) return 0;

	// mp_randomspawn_cmd(random);

	return 1;
}

int p_mp_reservations(char* text, int* consumed){
	char* reservations;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &reservations);
	if (!check) return 0;

	// mp_reservations_cmd(reservations);

	return 1;
}

int p_mp_respawndelay(char* text, int* consumed){
	int delay;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &delay);
	if (!check) return 0;

	// mp_respawndelay_cmd(delay);

	return 1;
}

int p_mp_roundlimit(char* text, int* consumed){
	int rounds;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &rounds);
	if (!check) return 0;

	// mp_roundlimit_cmd(rounds);

	return 1;
}

int p_mp_roundtime(char* text, int* consumed){
	int time;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &time);
	if (!check) return 0;

	// mp_roundtime_cmd(time);

	return 1;
}

int p_mp_startmoney(char* text, int* consumed){
	int money;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &money);
	if (!check) return 0;

	// mp_startmoney_cmd(money);

	return 1;
}

int p_mp_supply_items(char* text, int* consumed){
	char* itemlist;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &itemlist);
	if (!check) return 0;

	// mp_supply_items_cmd(itemlist);

	return 1;
}

int p_mp_teamkillpenalty(char* text, int* consumed){
	int kills;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &kills);
	if (!check) return 0;

	// mp_teamkillpenalty_cmd(kills);

	return 1;
}

int p_mp_teleportreload(char* text, int* consumed){
	int reload;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &reload);
	if (!check) return 0;

	// mp_teleportreload_cmd(reload);

	return 1;
}

int p_mp_tempbantime(char* text, int* consumed){
	int time;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &time);
	if (!check) return 0;

	// mp_tempbantime_cmd(time);

	return 1;
}

int p_mp_timelimit(char* text, int* consumed){
	int time;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &time);
	if (!check) return 0;

	// mp_timelimit_cmd(time);

	return 1;
}

int p_mp_tkpunish(char* text, int* consumed){
	int kill;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &kill);
	if (!check) return 0;

	// mp_tkpunish_cmd(kill);

	return 1;
}

int p_mp_trace(char* text, int* consumed){
	int accuracy;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &accuracy);
	if (!check) return 0;

	// mp_trace_cmd(accuracy);

	return 1;
}

int p_mp_turretdamage(char* text, int* consumed){
	int damage;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &damage);
	if (!check) return 0;

	// mp_turretdamage_cmd(damage);

	return 1;
}

int p_mp_unbuildable(char* text, int* consumed){
	char* buildings;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &buildings);
	if (!check) return 0;

	// mp_unbuildable_cmd(buildings);

	return 1;
}

int p_mp_unbuyable(char* text, int* consumed){
	char* unbuyable;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &unbuyable);
	if (!check) return 0;

	// mp_unbuyable_cmd(unbuyable);

	return 1;
}

int p_mp_vulnerablehostages(char* text, int* consumed){
	int vulnerable;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &vulnerable);
	if (!check) return 0;

	// mp_vulnerablehostages_cmd(vulnerable);

	return 1;
}

int p_mp_winlimit(char* text, int* consumed){
	int wins;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &wins);
	if (!check) return 0;

	// mp_winlimit_cmd(wins);

	return 1;
}

int p_mp_wpndmg(char* text, int* consumed){
	char* name; int damage;  // declarations
	char* check = tokenize(text, consumed, "\x2" "si", &name, &damage);
	if (!check) return 0;

	// mp_wpndmg_cmd(name, damage);

	return 1;
}

int p_mp_wpndmg_z1(char* text, int* consumed){
	char* name; int damage;  // declarations
	char* check = tokenize(text, consumed, "\x2" "si", &name, &damage);
	if (!check) return 0;

	// mp_wpndmg_z1_cmd(name, damage);

	return 1;
}

int p_mp_wpndmg_z2(char* text, int* consumed){
	char* name; int damage;  // declarations
	char* check = tokenize(text, consumed, "\x2" "si", &name, &damage);
	if (!check) return 0;

	// mp_wpndmg_z2_cmd(name, damage);

	return 1;
}

int p_mp_zombiedmg(char* text, int* consumed){
	int percentage;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &percentage);
	if (!check) return 0;

	// mp_zombiedmg_cmd(percentage);

	return 1;
}

int p_mp_zombiekillequip(char* text, int* consumed){
	int weapon;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &weapon);
	if (!check) return 0;

	// mp_zombiekillequip_cmd(weapon);

	return 1;
}

int p_mp_zombiekillscore(char* text, int* consumed){
	int kill;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &kill);
	if (!check) return 0;

	// mp_zombiekillscore_cmd(kill);

	return 1;
}

int p_mp_zombierecover(char* text, int* consumed){
	int recover;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &recover);
	if (!check) return 0;

	// mp_zombierecover_cmd(recover);

	return 1;
}

int p_mp_zombiespeedmod(char* text, int* consumed){
	int speedmod;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &speedmod);
	if (!check) return 0;

	// mp_zombiespeedmod_cmd(speedmod);

	return 1;
}

int p_msg(char* text, int* consumed){
	char* message;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &message);
	if (!check) return 0;

	// msg_cmd(message);

	return 1;
}

int p_rcon(char* text, int* consumed){
	char* commands;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &commands);
	if (!check) return 0;

	// rcon_cmd(commands);

	return 1;
}

int p_rcon_password(char* text, int* consumed){
	char* password;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &password);
	if (!check) return 0;

	// rcon_password_cmd(password);

	return 1;
}

int p_rcon_pw(char* text, int* consumed){
	char* password;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &password);
	if (!check) return 0;

	// rcon_pw_cmd(password);

	return 1;
}

int p_removeitem(char* text, int* consumed){
	int item;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &item);
	if (!check) return 0;

	// removeitem_cmd(item);

	return 1;
}

int p_reroute(char* text, int* consumed){
	int player; char* address;  // declarations
	char* check = tokenize(text, consumed, "\x2" "is", &player, &address);
	if (!check) return 0;

	// reroute_cmd(player, address);

	return 1;
}

int p_restart(char* text, int* consumed){
	int delay;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &delay);
	if (!check) return 0;

	// restart_cmd(delay);

	return 1;
}

int p_restartround(char* text, int* consumed){
	int delay;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &delay);
	if (!check) return 0;

	// restartround_cmd(delay);

	return 1;
}

int p_setarmor(char* text, int* consumed){
	int player; int armor;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &armor);
	if (!check) return 0;

	// setarmor_cmd(player, armor);

	return 1;
}

int p_setdeaths(char* text, int* consumed){
	int player; int deaths;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &deaths);
	if (!check) return 0;

	// setdeaths_cmd(player, deaths);

	return 1;
}

int p_sethealth(char* text, int* consumed){
	int player; int health;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &health);
	if (!check) return 0;

	// sethealth_cmd(player, health);

	return 1;
}

int p_setmaxhealth(char* text, int* consumed){
	int player; int maxhealth;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &maxhealth);
	if (!check) return 0;

	// setmaxhealth_cmd(player, maxhealth);

	return 1;
}

int p_setmoney(char* text, int* consumed){
	int player; int money;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &money);
	if (!check) return 0;

	// setmoney_cmd(player, money);

	return 1;
}

int p_setname(char* text, int* consumed){
	int player; char* name;  // declarations
	char* check = tokenize(text, consumed, "\x2" "is", &player, &name);
	if (!check) return 0;

	// setname_cmd(player, name);

	return 1;
}

int p_setpos(char* text, int* consumed){
	int player; int x; int y;  // declarations
	char* check = tokenize(text, consumed, "\x3" "iii", &player, &x, &y);
	if (!check) return 0;

	// setpos_cmd(player, x, y);

	return 1;
}

int p_setscore(char* text, int* consumed){
	int player; int score;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &score);
	if (!check) return 0;

	// setscore_cmd(player, score);

	return 1;
}

int p_setweapon(char* text, int* consumed){
	int player; int weapon;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &weapon);
	if (!check) return 0;

	// setweapon_cmd(player, weapon);

	return 1;
}

int p_shake(char* text, int* consumed){
	int player; int power;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &power);
	if (!check) return 0;

	// shake_cmd(player, power);

	return 1;
}

int p_slap(char* text, int* consumed){
	char* player;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &player);
	if (!check) return 0;

	// slap_cmd(player);

	return 1;
}

int p_spawnitem(char* text, int* consumed){
	int item; int x; int y;  // declarations
	char* check = tokenize(text, consumed, "\x3" "iii", &item, &x, &y);
	if (!check) return 0;

	// spawnitem_cmd(item, x, y);

	return 1;
}

int p_spawnnpc(char* text, int* consumed){
	int type; int x; int y; int rot;  // declarations
	char* check = tokenize(text, consumed, "\x4" "iiii", &type, &x, &y, &rot);
	if (!check) return 0;

	// spawnnpc_cmd(type, x, y, rot);

	return 1;
}

int p_spawnobject(char* text, int* consumed){
	int type; int x; int y; int rot; int mode; int team; int player;  // declarations
	char* check = tokenize(text, consumed, "\x7" "iiiiiii", &type, &x, &y, &rot, &mode, &team, &player);
	if (!check) return 0;

	// spawnobject_cmd(type, x, y, rot, mode, team, player);

	return 1;
}

int p_spawnplayer(char* text, int* consumed){
	int player; int x; int y;  // declarations
	char* check = tokenize(text, consumed, "\x3" "iii", &player, &x, &y);
	if (!check) return 0;

	// spawnplayer_cmd(player, x, y);

	return 1;
}

int p_speedmod(char* text, int* consumed){
	int player; int speedmod;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &speedmod);
	if (!check) return 0;

	// speedmod_cmd(player, speedmod);

	return 1;
}

int p_strip(char* text, int* consumed){
	int player; int weapon;  // declarations
	char* check = tokenize(text, consumed, "\x2" "ii", &player, &weapon);
	if (!check) return 0;

	// strip_cmd(player, weapon);

	return 1;
}

int p_sv_fow(char* text, int* consumed){
	int fow;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &fow);
	if (!check) return 0;

	// sv_fow_cmd(fow);

	return 1;
}

int p_sv_friendlyfire(char* text, int* consumed){
	int FF;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &FF);
	if (!check) return 0;

	// sv_friendlyfire_cmd(FF);

	return 1;
}

int p_sv_gamemode(char* text, int* consumed){
	int mode;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &mode);
	if (!check) return 0;

	// sv_gamemode_cmd(mode);

	return 1;
}

int p_sv_gm(char* text, int* consumed){
	int mode;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &mode);
	if (!check) return 0;

	// sv_gm_cmd(mode);

	return 1;
}

int p_sv_hostport(char* text, int* consumed){
	int port;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &port);
	if (!check) return 0;

	// sv_hostport_cmd(port);

	return 1;
}

int p_sv_lan(char* text, int* consumed){
	int lan;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &lan);
	if (!check) return 0;

	// sv_lan_cmd(lan);

	return 1;
}

int p_sv_map(char* text, int* consumed){
	char* map;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &map);
	if (!check) return 0;

	// sv_map_cmd(map);

	return 1;
}

int p_sv_maptransfer(char* text, int* consumed){
	int transfer;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &transfer);
	if (!check) return 0;

	// sv_maptransfer_cmd(transfer);

	return 1;
}

int p_sv_maxplayers(char* text, int* consumed){
	int players;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &players);
	if (!check) return 0;

	// sv_maxplayers_cmd(players);

	return 1;
}

int p_sv_msg(char* text, int* consumed){
	char* message;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &message);
	if (!check) return 0;

	// sv_msg_cmd(message);

	return 1;
}

int p_sv_msg2(char* text, int* consumed){
	int player; char* message;  // declarations
	char* check = tokenize(text, consumed, "\x2" "is", &player, &message);
	if (!check) return 0;

	// sv_msg2_cmd(player, message);

	return 1;
}

int p_sv_name(char* text, int* consumed){
	char* name;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &name);
	if (!check) return 0;

	// sv_name_cmd(name);

	return 1;
}

int p_sv_password(char* text, int* consumed){
	char* password;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &password);
	if (!check) return 0;

	// sv_password_cmd(password);

	return 1;
}

int p_sv_rcon(char* text, int* consumed){
	char* rcon;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &rcon);
	if (!check) return 0;

	// sv_rcon_cmd(rcon);

	return 1;
}

int p_sv_restart(char* text, int* consumed){
	int delay;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &delay);
	if (!check) return 0;

	// sv_restart_cmd(delay);

	return 1;
}

int p_sv_restartround(char* text, int* consumed){
	int delay;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &delay);
	if (!check) return 0;

	// sv_restartround_cmd(delay);

	return 1;
}

int p_sv_sound(char* text, int* consumed){
	char* soundfile;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &soundfile);
	if (!check) return 0;

	// sv_sound_cmd(soundfile);

	return 1;
}

int p_sv_sound2(char* text, int* consumed){
	int player; char* soundfile;  // declarations
	char* check = tokenize(text, consumed, "\x2" "is", &player, &soundfile);
	if (!check) return 0;

	// sv_sound2_cmd(player, soundfile);

	return 1;
}

int p_sv_specmode(char* text, int* consumed){
	int mode;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &mode);
	if (!check) return 0;

	// sv_specmode_cmd(mode);

	return 1;
}

int p_sv_spraytransfer(char* text, int* consumed){
	int spray;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &spray);
	if (!check) return 0;

	// sv_spraytransfer_cmd(spray);

	return 1;
}

int p_sv_usgnonly(char* text, int* consumed){
	int usgn;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &usgn);
	if (!check) return 0;

	// sv_usgnonly_cmd(usgn);

	return 1;
}

int p_transfer_speed(char* text, int* consumed){
	int speed;  // declarations
	char* check = tokenize(text, consumed, "\x1" "i", &speed);
	if (!check) return 0;

	// transfer_speed_cmd(speed);

	return 1;
}

int p_trigger(char* text, int* consumed){
	char* trigger;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &trigger);
	if (!check) return 0;

	// trigger_cmd(trigger);

	return 1;
}

int p_unban(char* text, int* consumed){
	char* banmask;  // declarations
	char* check = tokenize(text, consumed, "\x1" "s", &banmask);
	if (!check) return 0;

	// unban_cmd(banmask);

	return 1;
}

int p_unbanall(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// unbanall_cmd();

	return 1;
}

int p_usgn_addserver(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// usgn_addserver_cmd();

	return 1;
}

int p_usgn_info(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\x0" "");
	if (!check) return 0;

	// usgn_info_cmd();

	return 1;
}


// p_xxx ends here




/* tokenizer splits the cmd into the args, returns the cmd-type
 *
	int c;char* s;float port;
	char* cmd = tokenize("  banip \"192.168.1.1\" 3.14",&c,"sf",&s,&port);
	printf("cmd: %s, ip:%s, port:%f, consumed:%d\n",cmd, s,port,c);
 *
 * fmt = s i f
 */
char* tokenize(char* text, int* consumed, char* fmt, ...){
	int min = *(fmt++);
	int i,j, quot = 0, nargs = strlen(fmt), term = 0;
	*consumed = 0;
	char* cmd = NULL;
	va_list args;
	va_start(args, fmt);

	for (i=-1;i<nargs;i++){
		char* buf = NULL;
		if ((!*text || term) && i>=min) {
			va_end(args);
			return cmd;
		}else if (!*text || term){
			printf("[Parse] Too few arguments.\n");
			return NULL;
		}

		while(*text && (*text == ' ' || *text == ';')){
			text++;(*consumed)++;
		}
		if (*text == '"'){
			quot=1;text++;(*consumed)++;
		}
		for(j=0;text[j];j++){
			// unquoted termination condition
			if (!quot && (text[j] == ' ' || text[j] == ';' || !text[j])){
				if (text[j] == ';') term = 1;
				buf = (char*)malloc(j+1);
				memcpy(buf, text, j);
				buf[j]='\0';
				while(text[j] == ' ' || text[j] == ';') j++;
				text+=j;
				break;
			// quoted termination condition
			} else if (quot && text[j] == '"'){
				buf = (char*)malloc(j+1);
				memcpy(buf, text, j);
				buf[j++]='\0';
				text+=j;
				break;
			}
		}
		if(!buf){
			buf = (char*)malloc(j);
			memcpy(buf, text, j);
			buf[j] = '\0';
			text+=j;
		}

		(*consumed)+=j;
		quot=0;
		if(i<0) {cmd=buf;continue;}
		switch(fmt[i]){
		case 's':{
			char** a = va_arg(args, char**);
			*a = buf;
			break;
		}
		case 'i':{
			int* a = va_arg(args, int*);
			sscanf(buf, "%d", a);
			break;
		}
		case 'f':{
			float* a = va_arg(args, float*);
			sscanf(buf, "%f", a);
			break;
		}
		default:
			printf("[Parse] Bad parser format '%c'\n",fmt[i]);
			va_end(args);
			return NULL;
		}

	}

	va_end(args);
	return cmd;
}

void init_parse(){
	parse_t = hashmap_new();
#define add(type) hashmap_put(parse_t, #type, &p_##type);

	add(banip);

#undef add

}

void parse(char* text){
	if (!*text) return;
	int consumed;
	char* type = tokenize(text,&consumed,"\0");
	parse_h handler;
	int err = hashmap_get(parse_t, (char*)type, (void**)(&handler));
	if (err != MAP_OK){
		printf("[Parse] Invalid command '%s'\n",type);
		return parse(text+consumed);
	}

	int status = handler(text,&consumed);
	if (!status){
		// pass
	}
	parse(text+consumed);
}


