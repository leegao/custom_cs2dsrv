/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk, FloooD
 */

#include <main.h>
#include <getopt.h>
#include "settings.h"

void parse_opts(int argc, char *argv[]){
	static struct option long_options[] = {
		{"cfg", required_argument, 0, 'c'},
		{"name", required_argument, 0, 0},
		{0, 0, 0, 0}
	};

	while (1){
		int option_index = 0;
		int c = getopt_long (argc, argv, "c:", long_options, &option_index);
		if (c<0) return;
		switch (c){
		case 'c':
			cfg_file = optarg;
			break;
		case 0:
			sv_name = (unsigned char*)optarg;
			break;
		default:
			return;
		}
	}
}

/**
 * \fn int main()
 * \brief initialize sockets and if a message was recieved, give it to the right function.
 * \return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[]){

	// Parses the commandline arguments
	parse_opts(argc, argv); // IE: ./server -cserver.cfg --name "My Server"

	/**
	 * Initalize variables, weapons, players and sockets
	 */

	int sock;
	struct sockaddr_in newclient;
	unsigned char buffer[MAX_BUF];
	int size;
	fd_set descriptor; //I don't know

	ClearAllPlayer();
	WeaponInit();
	ReadServerCfg(cfg_file ? cfg_file:"server.cfg"); // Reads the server.cfg file (We can also check argv for --cfg or -c flag

	sock = create_socket();
	bind_socket(&sock, INADDR_ANY, sv_hostport);
	atexit(cleanup);

	//struct in_addr usgnip = GetIp("usgn.de");
	/*
	 FD_ZERO(&descriptor);
	 FD_SET(readsocket, &descriptor);
	 */
	OnServerStart();
	ReadMap();
	//if (argc == 1) //modify into optional offline mode
	//UsgnRegister(sock);

	init_queue(&send_q);
	start_stream();

	stream* s = init_stream(NULL);
	write_str(s, "abc\nabc");
	//byte* i = Stream.read(s, 2);
	int i = read_str(s);

	printf("%d %s %d\n",s -> mem, i, s->size);
	/**
	 * \var needed for ExecuteFunctionsWithTime()
	 */
	time_t checktime;
	time(&checktime);
#ifdef _WIN32

#else
	const int inc = NS_PER_S / sv_fps;
	int frame = 0;
	int previous = 0;

	struct timespec current, next;
	clock_gettime(CLOCK_MONOTONIC, &next);
#endif

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0; //1ms = 1000
	while (1)
	{

#ifdef _WIN32
#else
		frame++;
		next.tv_nsec += inc;
		while (next.tv_nsec > NS_PER_S)
		{
			next.tv_nsec -= NS_PER_S;
			next.tv_sec++;

			fpsnow = frame - previous;
			previous = frame;
			//printf("current fps: %d\n", fpsnow); //debugging
		}
#endif

		UpdateBuffer();
		CheckForTimeout(sock);
		ExecuteFunctionsWithTime(&checktime, sock); // refactor into scheduler
		CheckAllPlayerForReload(sock);

		FD_ZERO(&descriptor);
		FD_SET(sock, &descriptor);
		select(sock + 1, &descriptor, NULL, NULL, &timeout);

		if (FD_ISSET(sock, &descriptor)){
			size = udp_recieve(sock, buffer, MAX_BUF, &newclient);

			if (size < 3) {
				perror("Invalid packet! (size < 3)\n");
			} else {
				int id = IsPlayerKnown(newclient.sin_addr, newclient.sin_port); /// Function returns id or -1 if unknown
				if (id){///When the player is known execute other commands as when the player is unknown
					if (ValidatePacket(buffer, id)){ ///Checks and raise the packet numbering if necessary
						PaketConfirmation(buffer, id, sock); ///If the numbering is even, send a confirmation
						player[id].lastpacket = mtime();
						int control = 1;
						int position = 2;
						/**
						 * This while construct splits the recieved UDP-message
						 * into cs2d-messages.
						 * Every packet function returns the count of read bytes.
						 */
						while (control)
						{
							int tempsize = size - position;

							unsigned char *message = malloc(tempsize);
							memcpy(message, buffer + position, tempsize);
							int rtn = 0;

							switch (message[0])
							//payload
							{
							case 1:
								rtn = confirmation_known(message, tempsize, id,
										sock);
								break;
							case 3:
								rtn = connection_setup_known(message, tempsize,
										newclient.sin_addr, newclient.sin_port,
										id);
								break;
							case 7:
								rtn = fire(message, tempsize, id, sock);
								break;
							case 8:
								rtn = advanced_fire(message, tempsize, id,
										sock);
								break;
							case 9:
								rtn = weaponchange(message, tempsize, id,
										sock);
								break;
							case 10:
								rtn = posupdaterun(message, tempsize, id,
										sock);
								break;
							case 11:
								rtn = posupdatewalk(message, tempsize, id,
										sock);
								break;
							case 12:
								rtn = rotupdate(message, tempsize, id,
										sock);
								break;
							case 13:
								rtn = posrotupdaterun(message, tempsize, id,
										sock);
								break;
							case 14:
								rtn = posrotupdatewalk(message, tempsize, id,
										sock);
								break;
							case 16:
								rtn = reload(message, tempsize, id, sock);
								break;
							case 20:
								rtn = teamchange(message, tempsize, id,
										sock);
								break;
							case 23:
								rtn = buy(message, tempsize, id, sock);
								break;
							case 24:
								rtn = drop(message, tempsize, id, sock);
								break;
							case 28:
								// Spray 28 - 0 - x x - y y - color
								rtn = spray(message, tempsize, id, sock);
								break;
							case 32:
								rtn
										= specpos(message, tempsize, id,
												sock);
								break;
							case 39:
								rtn = respawnrequest(message, tempsize, id,
										sock);
								break;
							case 236:
								rtn
										= rcon_pw(message, tempsize, id,
												sock);
								break;
							case 240:
								rtn = chatmessage(message, tempsize, id,
										sock);
								break;
							case 249:
								rtn = ping_ingame(message, tempsize, id,
										sock);
								break;
							case 252:
								rtn = joinroutine_known(message, tempsize, id,
										sock);
								break;
							case 253:
								rtn = leave(id, sock);
								break;
							default:
								SendMessageToPlayer(id, "Not implemented yet!",
										1, sock);
								unknown(message, tempsize, buffer, size,
										position);
								rtn = tempsize;
								break;
							}

							position = position + rtn;
							if (position == size)
							{
								free(message);
								break;
							}
							/**
							 * Security check (Buffer Overflow)
							 */
							else if (position > size)
							{
								printf("Error while reading packet: position(%d) > size(%d)\n", position, size);
								free(message);
							}
							free(message);
						}
					}
				}
				else
				{
					int control = 1;
					int position = 2;
					while (control)
					{
						int tempsize = size - position;

						unsigned char *message = malloc(tempsize);
						memcpy(message, buffer + position, tempsize);
						int rtn = 0;

						switch (message[0])
						//payload
						{
						case 1:
							rtn = confirmation_unknown(message, tempsize,
									newclient.sin_addr, newclient.sin_port);
							break;
						case 3:
							rtn = connection_setup_unknown(message, tempsize,
									newclient.sin_addr, newclient.sin_port);
							break;
						case 27:
							rtn = UsgnPacket(27, message, tempsize, sock);
							break;
						case 28:
							rtn = UsgnPacket(28, message, tempsize, sock);
							break;
						case 250:
							rtn = ping_serverlist(message, tempsize,
									&newclient, sock);
							break;
						case 251:
							rtn = serverinfo_request(message, tempsize,
									&newclient, sock);
							break;
						case 252:
							rtn = joinroutine_unknown(message, tempsize,
									&newclient, sock);
							break;
						default:
							unknown(message, tempsize, buffer, size, position);
							rtn = tempsize;
							break;
						}

						position = position + rtn;
						if (position == size)
						{
							free(message);
							break;
						}
						/**
						 * Security check (Buffer Overflow)
						 */
						else if (position > size)
						{
							printf("Error while reading packet: position(%d) > size(%d)\n", position, size);
							free(message);
						}
						free(message);
					}
				}
			}
		}

		check_sendqueue(sock);

#ifdef _WIN32
		Sleep(1000 / sv_fps); //who cares about windows :D
#else
		clock_gettime(CLOCK_MONOTONIC, &current);
		if (((current.tv_sec == next.tv_sec)
				&& (current.tv_nsec < next.tv_nsec))
				|| (current.tv_sec < next.tv_sec))
		{
			clock_nanosleep(CLOCK_MONOTONIC,
				TIMER_ABSTIME, &next, NULL);
		}
		else //THIS IS LAGGGGGGGGGGGGGGGGGGGGG
		{
			next.tv_nsec = current.tv_nsec +
				(current.tv_sec - next.tv_sec) * NS_PER_S;
		}
#endif
	}
	return EXIT_SUCCESS;
}
