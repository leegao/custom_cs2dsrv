/*
 * parse_cmds.h
 *
 *  Created on: Apr 1, 2011
 *      Author: leegao
 */

#ifndef PARSE_CMDS_H_
#define PARSE_CMDS_H_


int banip_cmd(char* ip, int duration);

int banname_cmd(char* name, int duration);

int bans_cmd();

int banusgn_cmd(int usgn, int duration);

int changelevel_cmd(char* map);

int changemap_cmd(char* map);

int customkill_cmd(int killer, char* weapon, int victim);

int deathslap_cmd(char* player);

int bot_add_cmd();

int bot_add_ct_cmd();

int bot_add_t_cmd();

int bot_count_cmd(int count);

int bot_jointeam_cmd(int team);

int bot_kill_cmd();

int bot_prefix_cmd(char* prefix);

int bot_remove_cmd();

int bot_remove_all_cmd();

int bot_remove_ct_cmd();

int bot_remove_t_cmd();

int bot_skill_cmd(int skill);

int bot_weapons_cmd(int weapons);

int effect_cmd(char* effect, int x, int y, int p1, int p2, int r, int g, int b);

int equip_cmd(int player, int weapon);

int explosion_cmd(int x, int y, int size, int damage, int source);

int flashplayer_cmd(int player, int intensity);

int flashposition_cmd(int x, int y, int intensity);

int hudtxt_cmd(int id, char* txt, int x, int y, int align);

int hudtxt2_cmd(int player, int id, char* txt, int x, int y, int align);

int hudtxtalphafade_cmd(int player, int id, int duration, float alpha);

int hudtxtcolorfade_cmd(int player, int id, int duration, int red, int green, int blue);

int hudtxtmove_cmd(int player, int id, int duration, int x, int y);

int items_cmd();

int kick_cmd(char* player, char* reason);

int killobject_cmd(int object);

int killplayer_cmd(int player);

int listbans_cmd();

int listplayers_cmd();

int logaddress_add_cmd(char* address);

int logaddress_remove_cmd(char* address);

int logaddress_removeall_cmd();

int lua_cmd(char* script);

int luareset_cmd();

int makect_cmd(char* player);

int makespec_cmd(char* player);

int maket_cmd(char* player);

int map_cmd(char* map);

int maps_cmd();

int mp_antispeeder_cmd(int antispeeder);

int mp_autogamemode_cmd(int autogamemode);

int mp_autoteambalance_cmd(int balance);

int mp_building_health_cmd(char* building, int price);

int mp_building_limit_cmd(char* building, int limit);

int mp_building_price_cmd(char* building, int price);

int mp_buytime_cmd(float time);

int mp_c4timer_cmd(int time);

int mp_curtailedexplosions_cmd(int curtailed);

int mp_damagefactor_cmd(float factor);

int mp_deathdrop_cmd(int drop);

int mp_dispenser_health_cmd(int health);

int mp_dispenser_money_cmd(int money);

int mp_dmspawnmoney_cmd(int money);

int mp_dropgrenades_cmd(int drop);

int mp_floodprot_cmd(int flood);

int mp_freezetime_cmd(int time);

int mp_grenaderebuy_cmd(int allowed);

int mp_hostagepenalty_cmd(int kills);

int mp_idleaction_cmd(int action);

int mp_idlekick_cmd(int idle);

int mp_idletime_cmd(int time);

int mp_infammo_cmd(int infinite);

int mp_kevlar_cmd(float percent);

int mp_kickpercent_cmd(float percent);

int mp_killbuildingmoney_cmd(int money);

int mp_killbuildings_cmd(int kill);

int mp_killinfo_cmd(int info);

int mp_killteambuildings_cmd(int mode);

int mp_lagcompensation_cmd(int max);

int mp_localrconoutput_cmd(int output);

int mp_luamap_cmd(int use);

int mp_luaserver_cmd(char* file);

int mp_mapgoalscore_cmd(int score);

int mp_mapvoteratio_cmd(float percent);

int mp_maxclientsip_cmd(int clients);

int mp_maxrconfails_cmd(int max);

int mp_natholepunching_cmd(int allow);

int mp_pinglimit_cmd(int limit);

int mp_postspawn_cmd(int time);

int mp_radar_cmd(int radar);

int mp_randomspawn_cmd(int random);

int mp_reservations_cmd(char* reservations);

int mp_respawndelay_cmd(int delay);

int mp_roundlimit_cmd(int rounds);

int mp_roundtime_cmd(float time);

int mp_startmoney_cmd(int money);

int mp_supply_items_cmd(char* itemlist);

int mp_teamkillpenalty_cmd(int kills);

int mp_teleportreload_cmd(int reload);

int mp_tempbantime_cmd(float time);

int mp_timelimit_cmd(float time);

int mp_tkpunish_cmd(int kill);

int mp_trace_cmd(int accuracy);

int mp_turretdamage_cmd(int damage);

int mp_unbuildable_cmd(char* buildings);

int mp_unbuyable_cmd(char* unbuyable);

int mp_vulnerablehostages_cmd(int vulnerable);

int mp_winlimit_cmd(int wins);

int mp_wpndmg_cmd(char* name, int damage);

int mp_wpndmg_z1_cmd(char* name, int damage);

int mp_wpndmg_z2_cmd(char* name, int damage);

int mp_zombiedmg_cmd(float percentage);

int mp_zombiekillequip_cmd(int weapon);

int mp_zombiekillscore_cmd(int kill);

int mp_zombierecover_cmd(int recover);

int mp_zombiespeedmod_cmd(int speedmod);

int msg_cmd(char* message);

int rcon_cmd(char* commands);

int rcon_password_cmd(char* password);

int rcon_pw_cmd(char* password);

int removeitem_cmd(int item);

int reroute_cmd(int player, char* address);

int restart_cmd(int delay);

int restartround_cmd(int delay);

int setarmor_cmd(int player, int armor);

int setdeaths_cmd(int player, int deaths);

int sethealth_cmd(int player, int health);

int setmaxhealth_cmd(int player, int maxhealth);

int setmoney_cmd(int player, int money);

int setname_cmd(int player, char* name);

int setpos_cmd(int player, int x, int y);

int setscore_cmd(int player, int score);

int setweapon_cmd(int player, int weapon);

int shake_cmd(int player, int power);

int slap_cmd(char* player);

int spawnitem_cmd(int item, int x, int y);

int spawnnpc_cmd(int type, int x, int y, int rot);

int spawnobject_cmd(int type, int x, int y, int rot, int mode, int team, int player);

int spawnplayer_cmd(int player, int x, int y);

int speedmod_cmd(int player, int speedmod);

int strip_cmd(int player, int weapon);

int sv_fow_cmd(int fow);

int sv_friendlyfire_cmd(int ff);

int sv_gamemode_cmd(int mode);

int sv_gm_cmd(int mode);

int sv_hostport_cmd(int port);

int sv_lan_cmd(int lan);

int sv_map_cmd(char* map);

int sv_maptransfer_cmd(int transfer);

int sv_maxplayers_cmd(int players);

int sv_msg_cmd(char* message);

int sv_msg2_cmd(int player, char* message);

int sv_name_cmd(char* name);

int sv_password_cmd(char* password);

int sv_rcon_cmd(char* rcon);

int sv_restart_cmd(int delay);

int sv_restartround_cmd(int delay);

int sv_sound_cmd(char* soundfile);

int sv_sound2_cmd(int player, char* soundfile);

int sv_specmode_cmd(int mode);

int sv_spraytransfer_cmd(int spray);

int sv_usgnonly_cmd(int usgn);

int transfer_speed_cmd(int speed);

int trigger_cmd(char* trigger);

int unban_cmd(char* banmask);

int unbanall_cmd();

int usgn_addserver_cmd();

int usgn_info_cmd();


#endif /* PARSE_CMDS_H_ */
