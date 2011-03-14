/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#include "packets.h"

/**
 * \fn int unknown(unsigned char *message, int length, unsigned char *buffer, int size, int position)
 * \brief every unknown packet lands here
 * \param *message pointer to the unknown message
 * \param length sizeof message
 * \param *buffer pointer to the udp-packet
 * \param size sizeof buffer
 * \param position where the unknown message in buffer begins
 * \return read bytes (specific: parameter length)
 */
int unknown(stream* packet, unsigned char *buffer,
		int pid){
	int i;
	printf("Unknown packet: %d\n",pid);
//	for (i = 2; i <= position - 1; i++){
//		eprintf("%d-", buffer[i]);
//	}
//	eprintf("\n\t");
	int l = packet->size;
	byte* msg = Stream.read(packet, l);
	for (i = 0; i <= l - 1; i++){
		eprintf("%d-", msg[i]);
	}
	eprintf("\n");
}

/**
 * \fn int connection_setup_unknown(unsigned char *message, int length, struct in_addr ip, unsigned short port)
 * \brief handles a connection setup for unknown player
 * \param *message pointer to the unknown message
 * \param length sizeof message
 * \param ip clients ip
 * \param port clients port
 * \return read bytes (specific: 3)
 */
int connection_setup_unknown(stream* packet,
		struct in_addr ip, unsigned short port){
	if (!Stream.read(packet, 2))
		printf("Invalid packet (connection_setup_unknown)!\n");
}

/**
 * \fn int connection_setup_known(unsigned char *message, int length, struct in_addr ip, unsigned short port)
 * \brief handles a connection setup for known player
 * \param *message pointer to the unknown message
 * \param length sizeof message
 * \param ip clients ip
 * \param port clients port
 * \return read bytes (specific: 3)
 */
int connection_setup_known(stream* packet,
		struct in_addr ip, unsigned short port, int id){
	if (!Stream.read(packet,2))
		printf("Invalid packet (connection_setup_known)!\n");
}

/**
 * \fn int ping_ingame(unsigned char *message, int length, int id)
 * \brief handles a answer from the server ingame ping. this function calculates the latency
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int ping_ingame(stream *packet, int id){
	if (!Stream.read(packet,4))
		printf("Invalid packet (ping_ingame)!\n");
	player[id].latency = mtime() - player[id].start;
}

/**
 * \fn int confirmation_unknown(unsigned char *message, int length, struct in_addr ip, unsigned short port)
 * \brief handles a confirmation for unknown player
 * \param *message pointer to the unknown message
 * \param length sizeof message
 * \param ip clients ip
 * \param port clients port
 * \return read bytes (specific: 3)
 */
int confirmation_unknown(stream* packet, struct in_addr ip, unsigned short port){
	if (!Stream.read(packet, 2))
		printf("Invalid packet (confirmation_unknown)!\n");
}

/**
 * \fn int confirmation_known(unsigned char *message, int length, int id)
 * \brief handles a confirmation for known player
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 3)
 */
void confirmation_known(stream *packet, int id){
	if (packet->size < 2)
		printf("Invalid packet (confirmation_known)!\n");
}

/**
 * \fn int fire(unsigned char *message, int length, int id)
 * \brief handles a fire
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 1)
 */
int fire(stream *packet, int id){
	switch (OnFire(id)){
	case 0:
		SendFireMessage(id);
		break;
	}
}

/**
 * \fn int advanced_fire(unsigned char *message, int length, int id)
 * \brief handles a advanced_fire (right click)
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 1)
 */
int advanced_fire(stream* packet, int id){
	unsigned int status = Stream.read_byte(packet);

	switch (OnAdvancedFire(id, status)){
	case 0:
		SendAdvancedFireMessage(id, status);
		break;
	}
}

/**
 * \fn int buy(stream* packet, int id)
 * \brief handles a buy request
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 3)
 */
int buy(stream* packet, int id){
	CHECK_STREAM(packet, 2);
	int wpnid = Stream.read_byte(packet);

	switch (OnBuyAttempt(id, wpnid))
	{
	case 0:
		OnBuy(id, wpnid);
		break;
	}
}

/**
 * \fn int rotupdate(stream* packet, int id)
 * \brief handles a rotation update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int rotupdate(stream* packet, int id){
	CHECK_STREAM(packet, 4);
	float temprotation = Stream.read_float(packet);
	if (temprotation >= -180 && temprotation <= 180)
		SendRotUpdate(id, (player[id].rotation = temprotation));
	Stream.read(packet, 3);
}

/**
 * \fn int posupdatewalk(stream* packet, int id)
 * \brief handles a position walk update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int posupdatewalk(stream* packet, int id)
{
	CHECK_STREAM(packet, 4);
	unsigned short tempx = Stream.read_short(packet);
	unsigned short tempy = Stream.read_short(packet);

	switch (OnMoveAttempt(id, tempx, tempy, 0))
	{
	case 0:
		SendPosUpdate(id, tempx, tempy, 0);
		player[id].x = tempx;
		player[id].y = tempy;
		break;
	case 1:
		SendPosUpdate(id, player[id].x, player[id].y, 0);
	}
}
/**
 * \fn int posupdaterun(stream* packet, int id)
 * \brief handles a position run update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int posupdaterun(stream* packet, int id){
	CHECK_STREAM(packet, 4);
	unsigned short tempx = Stream.read_short(packet);
	unsigned short tempy = Stream.read_short(packet);
	switch (OnMoveAttempt(id, tempx, tempy, 0)){
	case 0:
		SendPosUpdate(id, tempx, tempy, 1);
		player[id].x = tempx;
		player[id].y = tempy;
		break;
	case 1:
		SendPosUpdate(id, player[id].x, player[id].y, 1);
	}
}
/**
 * \fn int posrotupdatewalk(stream* packet, int id))
 * \brief handles a position walk and rotation update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 9)
 */
int posrotupdatewalk(stream* packet, int id)
{
	CHECK_STREAM(packet, 8);
	unsigned short tempx = Stream.read_short(packet);
	unsigned short tempy = Stream.read_short(packet);
	float rotation = Stream.read_float(packet);
	if (rotation >= -180 && rotation <= 180)
	{
		switch (OnMoveAttempt(id, tempx, tempy, 0))
		{
		case 0:
			//if(rotation < 0) rotation += 360;
			SendPosRotUpdate(id, tempx, tempy, 0, rotation);
			player[id].rotation = rotation;
			player[id].x = tempx;
			player[id].y = tempy;
			break;
		case 1:
			SendPosRotUpdate(id, player[id].x, player[id].y, 0, player[id].rotation); // no change?
		}
	}
}

/**
 * \fn int posrotupdaterun(stream* packet, int id))
 * \brief handles a position run and rotation update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 9)
 */
int posrotupdaterun(stream* packet, int id){
	CHECK_STREAM(packet, 8);
	unsigned short tempx = Stream.read_short(packet);
	unsigned short tempy = Stream.read_short(packet);
	float rotation = Stream.read_float(packet);

	if (rotation >= -180 && rotation <= 180){
		switch (OnMoveAttempt(id, tempx, tempy, 1)){
		case 0:
			SendPosRotUpdate(id, tempx, tempy, 1, rotation);
			player[id].rotation = rotation;
			player[id].x = tempx;
			player[id].y = tempy;
			break;
		case 1:
			SendPosRotUpdate(id, player[id].x, player[id].y, 1, player[id].rotation);
		}
	}
}

/**
 * \fn int respawnrequest(stream* packet, int id)
 * \brief handles a respawn request
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 1)
 */
int respawnrequest(stream* packet, int id)
{
	int tmp;
	switch (OnRespawnRequest(id)){
	case 0:
		// srand(time(NULL)); // This is fucking stupid, srand then rand -> predictable pattern in most cases
		switch (player[id].team){
		case 0:
			printf("%s tried to spawn as spectator!\n", player[id].name);
			break;
		case 1:
			tmp = rand() % tspawncount;
			printf("%s spawned as a terrorist.\n", player[id].name);
			player[id].health = 100;
			player[id].dead = 0;
			player[id].x = (tspawnx[tmp] + 0.5) * 32;
			player[id].y = (tspawny[tmp] + 0.5) * 32;
			SendSpawnMessage(id, player[id].x, player[id].y);
			break;
		case 2:
			tmp = rand() % ctspawncount;
			printf("%s spawned as a counter-terrorist.\n", player[id].name);
			player[id].health = 100;
			player[id].dead = 0;
			player[id].x = (ctspawnx[tmp] + 0.5) * 32;
			player[id].y = (ctspawny[tmp] + 0.5) * 32;
			SendSpawnMessage(id, player[id].x, player[id].y);
			break;
		}
		break;
	}
}
/**
 * \fn int weaponchange(stream* packet, int id)
 * \brief handles a weapon change
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 3)
 */
int weaponchange(stream* packet, int id)
{
	CHECK_STREAM(packet, 2);

	byte wpnid = Stream.read_byte(packet);
	switch (OnWeaponChangeAttempt(id, wpnid)){
	case 0:
		SendWeaponChangeMessage(id, wpnid);
	}
}

/**
 * \fn int teamchange(stream* packet, int id)
 * \brief handles a team change
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 3)
 */
int teamchange(stream* packet, int id){
	CHECK_STREAM(packet, 2);
	unsigned char team = Stream.read_byte(packet);
	unsigned char skin = Stream.read_byte(packet);

	switch (OnTeamChangeAttempt(id, team, skin)){
	case 0:
		player[id].team = team;
		if (skin != 5) player[id].skin = skin;
		OnTeamChange(id, team, skin);
	}
}
/**
 * \fn int ping_serverlist(stream* packet, struct sockaddr_in *client)
 * \brief handles a team change
 * \param *message pointer to the message
 * \param length sizeof message
 * \param *client pointer to the client information structure
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int ping_serverlist(stream* packet, struct sockaddr_in *client, int writesocket){
	CHECK_STREAM(packet, 3);

	unsigned char *tempbuffer = malloc(packet->size+3);
	if (tempbuffer == NULL)
		error_exit("Memory error ( ping_serverlist() )");

	tempbuffer[0] = 0x01;
	tempbuffer[1] = 0x00;
	tempbuffer[2] = packet->mem[0];
	tempbuffer[3] = packet->mem[1];
	tempbuffer[4] = packet->mem[2];
	//memcpy(tempbuffer + 3, packet->mem, packet->size);

	//send_now(tempbuffer, 5, *client);
	udp_send(writesocket, tempbuffer, 5, client);
	free(tempbuffer);
}

int serverinfo_request(stream* packet,
		struct sockaddr_in *client)
{
	CHECK_STREAM(packet,1);
	byte* message = packet->mem;
	stream* buf = init_stream(NULL);
	if (!buf)
		error_exit("Memory error ( serverinfo_request() )");

	Stream.write_short(buf, 1);
	Stream.write_byte(buf, 0xfb);
	Stream.write_byte(buf, Stream.read_byte(packet));

	switch (message[1])
	{
	case 1:
	case 2:
		Stream.write_byte(buf, GetServerStatus());
		Stream.write_str(buf, sv_name);
		Stream.write_str(buf, sv_map);
		Stream.write_byte(buf, onlineplayer);
		Stream.write_byte(buf, sv_maxplayers);
		if (sv_gamemode != 0)
			Stream.write_byte(buf, sv_gamemode);
		Stream.write_byte(buf, bot_count);
		send_now(buf->mem, buf->size, *client);
		//udp_send(writesocket, buffer, stringsize, client);
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
	free(buf);
}

int joinroutine_unknown(stream* packet, struct sockaddr_in *client){
	CHECK_STREAM(packet, 1);
	switch (Stream.read_byte(packet)){
	case 0x00:{
		int i;
		for (i = 1; i < MAX_CLIENTS; i++){
			if (player[i].used != 1){
				player[i].used = 1;
				player[i].ip = client->sin_addr;
				player[i].port = client->sin_port;
				player[i].joinstatus = 1;
				player[i].client_number = 4; // wtf?
				player[i].server_number = 2; // and wtf is this?
				break;
			}
		}
		stream* buf = init_stream(NULL);
		if (!buf)
			error_exit("Memory error ( joinroutine_unknown() )");

		Stream.write_short(buf, 1);
		Stream.write_short(buf, 0xfc);
		Stream.write_str(buf, pre_authcode);

		send_now(buf->mem, buf->size, *client);
		//udp_send(writesocket, buffer, stringsize, client);

		free(buf);
		break;
	}
	default:
		printf("Unexpected join data\n");
	}
}

int specpos(stream* packet, int id){
	CHECK_STREAM(packet, 8);
	int x = Stream.read_int(packet);
	int y = Stream.read_int(packet);

	switch (OnSpecmove(id, x, y)){
	case 0:
		player[id].specposx = x;
		player[id].specposy = y;
	}
}

int chatmessage(stream* packet, int id){
	CHECK_STREAM(packet, 4);
	unsigned char team, unknown;
	int paketsize;

	team = Stream.read_byte(packet);
	Stream.read_str(packet);

	unknown = Stream.read_byte(packet);

	unsigned char *string = malloc(paketsize);
	if (string == NULL)
		error_exit("Memory error ( chatmessage() )\n");
	memcpy(string, message + position, paketsize);

	string[paketsize] = '\0';
	position += paketsize;

	switch (OnChatMessage(id, string, team))
	{
	case 0:
		SendChatMessage(id, string, team);
		break;
	case 1:
		break;
	default:
		printf("Unknown Return value for OnChatMessage()!\n");
		break;
	}

	free(string);

	return paketlength;
}

int joinroutine_known(stream* packet, int id)
{
	int paketlength = 2;
	if (paketlength > length)
	{
		printf("Invalid packet (joinroutine_known)!\n");
		return length;
	}
	switch (message[1])
	{
	case 0:
	{
		paketlength = 2;
		if (paketlength > length)
		{
			printf("Invalid packet (joinroutine_known)!\n");
			return length;
		}
		break;
	}
	case 1:
	{
		if (player[id].joinstatus == 1)
		{
			paketlength = 16; // ???
			if (paketlength > length)
			{
				printf("Invalid packet (joinroutine_known)!\n");
				return length;
			}

			int position = 2;
			//Playername
			int stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Playername too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			player[id].name = malloc(stringsize + 1);
			if (player[id].name == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(player[id].name, message + position, stringsize);
			player[id].name[stringsize] = '\0';
			position += stringsize; //+1 because after it there is a null byte, so ignore it

			//printf("Player %s connected..\n", player[id].name);

			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Password too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			unsigned char *password = malloc(stringsize + 1);
			if (password == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(password, message + position, stringsize);
			password[stringsize] = '\0';
			position += stringsize;

			//printf("\tPassword: ");
			/*
			 int i;
			 for (i = 0; i <= u_strlen(password); i++)
			 {
			 printf("%d-", password[i]);
			 }
			 printf("\n");
			 */

			//Encryption String
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Encryption too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			unsigned char *encryption1 = malloc(stringsize + 1);
			if (encryption1 == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(encryption1, message + position, stringsize);
			encryption1[stringsize] = '\0';
			position += stringsize;

			//printf("\tEncryptionstring: %s\n", encryption1);

			//Player Version
			player[id].version = message[position];
			position++;
			//printf("\tVersion: %d\n", player[id].version);
			position++; //Null-byte


			//USGN ID
			player[id].usgn = malloc(sizeof(unsigned short));
			if (player[id].usgn == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(player[id].usgn, message + position, 2); //sizeof(unsigned short) == 2
			position += 4; //2 bytes + 2 null bytes
			/*
			 #else
			 *player[id].usgn = endian_swap_short(player[id].usgn);
			 #endif
			 */
			//printf("\tUSGN-ID: %u\n", *player[id].usgn);


			//Spraylogo
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Spraylogoname too big\n");
				return length;
			};
			paketlength += stringsize;
			position++;

			player[id].spraylogo = malloc(stringsize + 1);
			if (player[id].spraylogo == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(player[id].spraylogo, message + position, stringsize);
			player[id].spraylogo[stringsize] = '\0';
			position += stringsize;

			//printf("\tSpraylogo: %s\n", player[id].spraylogo);


			//Map-Hash
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Map-Hash too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			unsigned char *maphash = malloc(stringsize + 1);
			if (maphash == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(maphash, message + position, stringsize);
			maphash[stringsize] = '\0';
			position += stringsize;

			//printf("\tMap-Hash: %s\n", maphash);

			position++; //Nullbyte

			//WIN
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("WIN too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			player[id].win = malloc(stringsize + 1);
			if (player[id].win == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(player[id].win, message + position, stringsize);
			player[id].win[stringsize] = '\0';
			position += stringsize;

			//printf("\tWIN: %s (%d)\n", player[id].win, u_strlen(player[id].win));

			unsigned char *buffer = NULL;
			stringsize = 0;
			int tempstatus = CheckPlayerData(password);
			switch (tempstatus)
			{
			case 0x00:
				stringsize = 6 + u_strlen(sv_map) + u_strlen(pre_authcode);
				buffer = malloc(stringsize);
				if (buffer == NULL)
					error_exit("Memory error ( joinroutine_known() )\n");

				position = 0;

				buffer[position] = 252;
				position++;
				buffer[position] = 2;
				position++;
				buffer[position] = 0; //Normal
				position++;
				buffer[position] = id;
				position++;
				buffer[position] = u_strlen(sv_map);
				position++;
				memcpy(buffer + position, sv_map, u_strlen(sv_map));
				position += u_strlen(sv_map);
				buffer[position] = u_strlen(pre_authcode);
				position++;
				memcpy(buffer + position, pre_authcode, u_strlen(pre_authcode));
				position += u_strlen(pre_authcode);
				player[id].joinstatus = 2;
				break;

			default:
			{
				stringsize = 3;
				buffer = malloc(stringsize);
				if (buffer == NULL)
					error_exit("Memory error ( joinroutine_known() )\n");

				position = 0;

				buffer[position] = 252;
				position++;
				buffer[position] = 2;
				position++;
				buffer[position] = tempstatus; //Everyone is banned (just for testing)
				position++;
				player[id].joinstatus = 0;
				break;
			}

			}
			//stringsize = 16 + u_strlen(sv_map);

			/*
			 0 - Normal
			 1 - Password wrong
			 2 - USGN only
			 3 - Server full
			 4 - Banned
			 5 - Another Game Version
			 6 - ??
			 7 - Can't validate user (USGN offline)
			 8 - ??
			 9 - Connection already exists
			 10 - Wrong client (pre_authcode)
			 11 - Diffrent map (temp, etc.)
			 12 - Map unknown (maptransfer disabled)
			 13++ - Failed to join
			 */

			if (stringsize != 0)
				SendToPlayer(buffer, stringsize, id, 1);

			free(encryption1);
			free(maphash);
			free(buffer);

			onlineplayer++;
		}
		else
		{
			printf("Unexpected join data (%d) from %s; expected %d\n", message[1], player[id].name, player[id].joinstatus+1);
		}
		break;
	}
	case 3:
	{
		if (player[id].joinstatus == 2)
		{
			int position = 2;

			paketlength = 5;
			if (paketlength > length)
			{
				printf("Invalid packet (joinroutine_known)!\n");
				return length;
			}

			//Map-Hash
			int stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Map-Hash too big\n");
				return length;
			}
			position++;

			unsigned char *maphash = malloc(stringsize + 1);
			if (maphash == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(maphash, message + position, stringsize);
			maphash[stringsize] = '\0';
			position += stringsize;
			paketlength += stringsize;

			//printf("\tMaphash: %s\n", maphash);

			//pre_authcode_respond
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("pre_authcon_respond too big\n");
				return length;
			}
			position++;

			unsigned char *pre_authcode_respond = malloc(stringsize + 1);
			if (pre_authcode_respond == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(pre_authcode_respond, message + position, stringsize);
			pre_authcode_respond[stringsize] = '\0';
			position += stringsize;
			paketlength += stringsize;

			//printf("\tpre_authcode_respond: %s\n", pre_authcode_respond);

			//Player Version
			//unsigned char mapstatus = message[position]; //avoid warning
			position++;
			//printf("\tMapstatus: %d\n", mapstatus);

			free(pre_authcode_respond);
			free(maphash);

			//Respond
			stringsize = 3;
			unsigned char *buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 4;
			position++;
			buffer[position] = 0; //CheckPlayerData()
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			player[id].joinstatus = 3;
		}
		else
		{
			printf("Unexpected join data (%d) from %s; expected %d\n", message[1], player[id].name, player[id].joinstatus+1);
		}
		break;
	}
	case 5:
	{
		if (player[id].joinstatus == 3)
		{
			int position = 2;

			paketlength = 3;
			if (paketlength > length)
			{
				printf("Invalid packet (joinroutine_known)!\n");
				return length;
			}
			//Map-Hash
			int stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Mapname too big\n");
				return length;
			}
			position++;

			unsigned char *mapname = malloc(stringsize + 1);
			if (mapname == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(mapname, message + position, stringsize);
			mapname[stringsize] = '\0';
			position += stringsize;
			paketlength += stringsize;

			//printf("\tMapname: %s\n", mapname);


			//----------- ServerData -----------

			stringsize = 28 + u_strlen(sv_map) + u_strlen(sv_name);
			unsigned char *buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 6;
			position++;
			buffer[position] = 0; //CheckPlayerData()
			position++;

			buffer[position] = u_strlen(sv_map);
			position++;
			memcpy(buffer + position, sv_map, u_strlen(sv_map));
			position += u_strlen(sv_map);

			buffer[position] = u_strlen(sv_name);
			position++;
			memcpy(buffer + position, sv_name, u_strlen(sv_name));
			position += u_strlen(sv_name);

			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = sv_friendlyfire;
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = mp_roundtime;
			position++;
			buffer[position] = mp_freezetime;
			position++;
			buffer[position] = mp_c4timer;
			position++;
			buffer[position] = 32; //Unknown
			position++;
			buffer[position] = 124; //Unknown
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = 1; //Unknown
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = sv_maxplayers;
			position++;
			buffer[position] = sv_fow;
			position++;
			buffer[position] = mp_specmode;
			position++;
			buffer[position] = sv_gamemode;
			position++;
			buffer[position] = mp_respawndelay;
			position++;
			buffer[position] = mp_infammo;
			position++;
			buffer[position] = 3; //u_strlen ACK
			position++;
			buffer[position] = 65; //A
			position++;
			buffer[position] = 67; //C
			position++;
			buffer[position] = 75; //K
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			free(buffer);

			//----------- PlayerData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 1;
			position++;
			buffer[position] = onlineplayer;
			position++;

			int i;
			for (i = 1; i <= sv_maxplayers; i++)
			{
				if (player[i].used == 1 && player[i].joinstatus >= 1 && i != id)
				{
					unsigned char *encodedname;
					encodedname = GetEncodedString(player[i].name, u_strlen(
							player[i].name));
					unsigned short *deaths = &player[i].deaths;
					unsigned short tempscore = (unsigned) (player[i].deaths
							+ 1000);
					unsigned short *score = &tempscore;

					unsigned short tempx = (player[i].x);
					unsigned short tempy = (player[i].y);
					unsigned short *x = &tempx;
					unsigned short *y = &tempy;

					float *ptemprotation = &player[i].rotation;

					int playersize = 25 + u_strlen(encodedname);
					buffer = realloc(buffer, position + 1 + playersize); //+1 because e.g. buffer[10] are 11 chars
					if (buffer == NULL)
						error_exit("Memory error ( joinroutine_known() )\n");

					buffer[position] = i;
					position++;

					buffer[position] = u_strlen(encodedname);
					position++;
					memcpy(buffer + position, encodedname,
							u_strlen(encodedname));
					position += u_strlen(encodedname);
					free(encodedname);

					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = player[i].team;
					position++;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = player[i].skin; //Unknown
					position++;
					/*
					 buffer[position] = score[0]; //Deaths
					 position++;
					 buffer[position] = score[1]; //Deaths
					 position++;
					 */
					memcpy(buffer + position, score, 2);
					position += 2;
					/*
					 buffer[position] = deaths[0]; //Deaths
					 position++;
					 buffer[position] = deaths[1]; //Deaths
					 position++;
					 */
					memcpy(buffer + position, deaths, 2);
					position += 2;
					memcpy(buffer + position, x, 2);
					position += 2;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = 0; //Unknown
					position++;
					memcpy(buffer + position, y, 2);
					position += 2;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = ptemprotation[0]; //Rotation
					position++;
					buffer[position] = ptemprotation[1]; //Rotation
					position++;
					buffer[position] = player[i].health; //Health
					position++;
					buffer[position] = player[i].armor; //Armor
					position++;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position]
							= player[i].actualweapon; //Aktuelle Waffe
					position++;
					buffer[position] = 0; //Unknown
					position++;
					/*
					 01 00 01 00 00 e8 03 00 00 70 00 00 00 70 01 00 00 7d ff 64 00 00 32 00
					 04 00 01 00 00 e8 03 00 00 0c 18 00 00 0c 18 00 00 66 ff 64 00 00 32 00
					 01 00 01 00 00 e8 03 00 00 00 01 00 00 00 01 00 00 12 00 64 00 00 32 00
					 01 00 02 00 00 e8 03 00 00 01 10 00 00 01 10
					 e8 03 00 00 12 01 00 00 01 03
					 e8 03 00 00 0c 18 00 00 0d 18 00 00 ab 00 64 00 00 1e 00
					 e8 03 00 00 10 18 00 00 10 18 00 00 b6 ff 64 c9 00 49 00
					 01 00 01 00 00 4c 04 96 00 10 18 00 00 10 18 00 00 5e ff 64 00 00 02 00
					 */
				}
			}
			if (1)
			{
				unsigned char *encodedname;
				encodedname = GetEncodedString(player[id].name, u_strlen(
						player[id].name));

				int playersize = 25 + u_strlen(encodedname);
				buffer = realloc(buffer, position + 1 + playersize); //+1 because e.g. buffer[10] are 11 chars
				if (buffer == NULL)
					error_exit("Memory error ( joinroutine_known() )\n");

				buffer[position] = id;
				position++;

				buffer[position] = u_strlen(encodedname);
				position++;
				memcpy(buffer + position, encodedname, u_strlen(encodedname));
				position += u_strlen(encodedname);
				free(encodedname);

				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = player[id].team;
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 232; //Unknown
				position++;
				buffer[position] = 3; //Unknown
				position++;
				buffer[position] = 0; //Deaths
				position++;
				buffer[position] = 0; //Deaths
				position++;
				buffer[position] = 0; //X
				position++;
				buffer[position] = 0; //X
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Y
				position++;
				buffer[position] = 0; //Y
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Health
				position++;
				buffer[position] = 0; //Armor
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Aktuelle Waffe 50 = Knife
				position++;
				buffer[position] = 0; //Unknown
				position++;
			}

			SendToPlayer(buffer, position, id, 1);
			free(buffer);

			//----------- PlayerData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 1; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			free(buffer);

			//----------- HostageData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 2; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			free(buffer);

			//----------- ItemData -----------

			/*
			 fc 07 03 01(1 anzahl) 01(id) 00 4b(waffenid) 0f 00 12 00 (position) 01 (munition ?) 00 00 00
			 */
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 3; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			free(buffer);

			//----------- EnityData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 4; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			free(buffer);

			//----------- DynamicObjectData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 5; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			free(buffer);

			//----------- ProjectileData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 6; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			free(buffer);

			//----------- DynamicObjectImageData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 7; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			free(buffer);

			//----------- Final ACK -----------
			stringsize = 7;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 200; //third payload
			position++;
			buffer[position] = 3; //u_strlen ACK
			position++;
			buffer[position] = 65; //A
			position++;
			buffer[position] = 67; //C
			position++;
			buffer[position] = 75; //K
			position++;

			SendToPlayer(buffer, stringsize, id, 1);
			free(buffer);

			player[id].joinstatus = 4;
			free(mapname);

			OnJoin(id);
		}
		else
		{
			printf("Unexpected join data (%d) from %s; expected %d\n", message[1], player[id].name, player[id].joinstatus+1);
		}
		break;
	}
	default:
	{
		printf("Unexpected join data (%d) from %s; expected %d\n", message[1], player[id].name, player[id].joinstatus+1);
	}
		break;
	}

	return paketlength;
}

int leave(int id)
{
	OnLeave(id);

	free(player[id].name);
	free(player[id].usgn);
	free(player[id].spraylogo);
	free(player[id].win);

	player[id].name = NULL;
	player[id].usgn = NULL;
	player[id].spraylogo = NULL;
	player[id].win = NULL;

	onlineplayer--;

	ClearPlayer(id);

	return 2;
}

int reload(stream* packet, int id)
{
	int paketlength = 2;
	if (length < paketlength)
	{
		printf("Invalid packet (buy)!\n");
		return length;
	}

	int position = 1;
	int status;

	status = message[position];
	position++;

	if (status == 1)
	{
		SendReloadMessage(id, 1);
		player[id].reloading = player[id].actualweapon;
		player[id].reloadtimer = mtime() + weapons[player[id].actualweapon].reloadtime;
	}
	return paketlength;
}

int spray(stream* packet, int id)
{
	// 28 0 xx yy c
	//  0 1 23 45 6
	struct
	{
		unsigned char hi;
		unsigned char lo;
	} x, y;

	if (length < 7)
	{
		printf("Invalid packet (spray)!\n");
		return length;
	}

	x.lo = message[2];
	x.hi = message[3];

	y.lo = message[4];
	y.hi = message[5];

	unsigned short xx = x.hi * 256 + x.lo, yy = y.hi * 256 + y.lo;
	unsigned char c = message[6];
	unsigned char i = (char) id;

	// Postprocessing if needed, then send back exact same data
	// xx and yy are positions, not tiles.

	SendSprayMessage(i, xx, yy, c);
	return 7;
}

int UsgnPacket(int packetid, stream* packet) //No check if really from usgn.de
{
	int paketlength = 2;
	switch (packetid)
	{
	case 27:
		if (message[1] == 1)
		{
			printf("[USGN] Server successfully added to the serverlist..\n");
		}
		else
		{
			printf("[USGN] Server NOT added to the serverlist.. (Code: %d)\n", message[3]);
		}
		paketlength = 2;
		break;
	case 28:
		if (message[1] == 2)
		{
			printf("[USGN] Server successfully updated in the serverlist..\n");
		}
		else
		{
			printf("[USGN] Server NOT updated in the serverlist.. (Code: %d)\n", message[3]);
		}
		paketlength = 2;
		break;
	default:
		printf("[USGN] Unknown Message recieved: ");
		int i;
		for (i = 0; i < length; i++)
		{
			eprintf("%d-", message[i]);
		}
		eprintf("\n");
		paketlength = length;
		break;
	}
	return paketlength;
}

int drop(stream* packet, int id)
{
	int paketlength = 7;
	if (length < paketlength)
	{
		printf("Invalid packet (drop)!\n");
		return length;
	}

	int position = 1;
	unsigned char wpnid, unknown1, unknown2, unknown3;
	unsigned short ammo1, ammo2;

	wpnid = message[position];
	position++;
	ammo1 = message[position];
	position++;
	unknown1 = message[position];
	position++;
	ammo2 = message[position];
	position++;
	unknown2 = message[position];
	position++;
	unknown3 = message[position];
	position++;

	switch (OnDrop(id, wpnid, ammo1, ammo2, unknown1, unknown2, unknown3))
	{
	case 0:
		SendDropMessage(id, wpnid, ammo1, ammo2, unknown1, unknown2, unknown3);
		break;
	default:
		break;
	}

	return paketlength;
}

int rcon_pw(stream* packet, int id)
{
	// 236 ln pw
	// 0 1 ln

	unsigned char key[] = "mysecretremotecontrolpmysecret";

	int expected = (int) (message[1]);
	if (length < expected + 2)
	{
		printf("Invalid packet (rcon_pw)!\n");
		return length;
	}

	char* pw = malloc(expected + 1);

	int i;
	for (i = 0; i < expected; i++)
	{
		//eprintf("%c", message[i+2]- key[i]);
		pw[i] = (unsigned char) (message[i + 2] - key[i]);
	}
	pw[expected] = '\0';

	// Check against actual rcon
	if (strcmp(pw, (char *)sv_rcon) == 0)
	{
		printf("[Rcon_pw] Success\n");
		player[id].rcon = 1;
		//SendRconPwMessage(id, message, length, 1);
	}
	else
	{
		printf("[Rcon_pw] Bad attempt by %s.\n", player[id].name);
		SendRconPwMessage(id, message, length, 0);
	}

	return length;
}



// auxiliary functions
//Stream.quanta = 0xff;
stream* init_stream(stream* s){
	if (!s || !s->n || !s->mem) s = (stream*)malloc(sizeof(struct stream_));
	s -> mem = (byte*)malloc(Stream.quanta);
	s -> cur = s->mem;
	s -> size = 0;
	s -> n = 1;
	return s;
}

byte* s__read__(stream* s, int n){
	byte* m = s->mem;
	if (n > s->size) return 0;
	s->size -= n;
	s->mem += n;
	return m;
	//return (byte*)(n<=s->size && (((s->size-=n) && 0) + ((s->mem+=n) && 0) + m));
}

int s__write__(stream* s, byte* a, int n){
	if (!s) return 0;
	if (!s->n || !s->mem) init_stream(s);
	int lg = (s->size + n) - (Stream.quanta*s->n);
	if (lg > 0) {
		byte* t = s->mem;
		s->mem = (byte*)malloc(Stream.quanta * (s->n += 1+lg/Stream.quanta));
		if (!s->mem) return 0;
		memcpy(s->mem, t, s->size);
		s->cur = s->mem+s->size;
	}
	//printf("%d %d\n", s->mem, s->cur);
	memcpy(s->cur, a, n);
	//return 0;
	s->cur+=n;
	s->size += n;
	return 1;
}

byte* s__peek__(stream* s){
	return s->mem;
}

int s__seek__(stream* s, int pos){
	if (pos < 0) return 0;
	if (pos < s->size) return (int)(s->cur = s->mem+pos);
	else return (int)(s->cur = s->mem + s->size);
}

int s__trim__(stream* s, int pos){
	if (pos < 0) return 0;
	if (pos < s->size) return
		((s->cur = s->mem+pos) && (s->size = pos));
	else return (int)(s->cur = s->mem + s->size);
}

// specific cases
byte read_byte(stream* s){
	byte* i = (byte*)Stream.read(s, 1);
	return i ? *i : 0u;
}

int write_byte(stream* s, byte c){
	return Stream.write(s, &c, 1);
}

short read_short(stream* s){
	short* i = (short*)Stream.read(s, 2);
	return i ? *i : 0;
}

int write_short(stream* s, short c){
	return Stream.write(s, (byte*)&c, 2);
}

int read_int(stream* s){
	int* i = (int*)Stream.read(s, 4);
	return i ? *i : 0;
}

int write_int(stream* s, int c){
	return Stream.write(s, (byte*)&c, 4);
}

float read_float(stream* s){
	float* f = (float*)Stream.read(s, 4);
	return f ? *f : 0.0;
}

int write_float(stream* s, float c){
	return Stream.write(s, (byte*)&c, 4);
}

byte* read_str(stream* s){
	byte i = read_byte(s);
	if (!i) return 0;
	byte* str = (byte*)malloc(i+1), *src = Stream.read(s, i);
	if (!src) return 0;
	memcpy(str, src, i);
	str[i] = 0;
	return str;
}

int write_str(stream* s, byte* str){
	int n = strlen((char*)str)+1;
	byte* str_ = (byte*)malloc(n--);
	memcpy(str_+1, str, n);
	*str_ = n++;
	return Stream.write(s, str_, n);
}

byte* read_line(stream* s){
	byte* raw = Stream.peek(s);
	int n = 0;
	while(*raw++ != '\n' && n < s->size)n++;
	if (!n) return 0;
	byte* str = (byte*)malloc(n+1), *src = Stream.read(s, n+1);
	memcpy(str, src, n);
	str[n] = 0;
	return str;
}

int write_line(stream* s, byte* str){
	int n = strlen((char*)str)+1;
	byte* str_ = (byte*)malloc(n--);
	memcpy(str_, str, n);
	str_[n++] = '\n';
	return Stream.write(s, str_, n);
}

void start_stream(){
	Stream.quanta = 0xff;
	Stream.read = &s__read__;
	Stream.write = &s__write__;
	Stream.peek = &s__peek__;
	Stream.seek = &s__seek__;
	Stream.trim = &s__trim__;

	Stream.read_byte = &read_byte;
	Stream.read_short = &read_short;
	Stream.read_int = &read_int;
	Stream.read_float = &read_float;
	Stream.read_str = &read_str;
	Stream.read_line = &read_line;

	Stream.write_byte = &write_byte;
	Stream.write_short = &write_short;
	Stream.write_int = &write_int;
	Stream.write_float = &write_float;
	Stream.write_str = &write_str;
	Stream.write_line = &write_line;
}
