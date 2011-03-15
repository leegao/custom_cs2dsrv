/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#include "cross_layer.h"
/**
 * \fn int create_socket(void)
 * \brief creates a socket
 * \return socketnumber or 0 if failed
 */
int create_socket(void)
{
#ifdef _WIN32

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,0), &wsa) != 0)
	{
		socket_error_exit("WSAStartup() failed");
	}
	else
	{
		int sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock < 0)
		{
			socket_error_exit("socket() failed");
		}
		return sock;
	}
#else

	const int y = 1;
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		socket_error_exit("socket() failed");
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));
	return sock;

#endif
	return 0;
}

/**
 * \fn int bind_socket(int *sock, unsigned long adress, unsigned short port)
 * \brief bind a socket to a specific IP and port
 * \param *sock socket to bind
 * \param adress ip-address to bind
 * \param port port to bind
 */
void bind_socket(int *sock, unsigned long adress, unsigned short port)
{
#ifdef _WIN32
	struct sockaddr_in server;

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(adress);
	server.sin_port = htons(port);
	if (bind(*sock, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR)
	{
		socket_error_exit("bind() failed");
	}
#else
	struct sockaddr_in server;
	memset(&server, 0, sizeof (server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(adress);
	server.sin_port = htons(port);
	if (bind(*sock, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		socket_error_exit("bind() failed");
	}
#endif
}

/**
 * \fn int error_exit(char *message)
 * \brief Show a error message and exit the programm
 * \param *message message to display
 */
void error_exit(char *message)
{
	printf("%s", message);
	/*
	 printf("%s: %d\n", message, WSAGetLastError());
	 //debug(stderr);
	 #else
	 printf("%s: %s\n", message, strerror(errno));
	 //debug(stderr);
	 */

	exit(EXIT_FAILURE);
}

/**
 * \fn int socket_error_exit(char *message)
 * \brief Show a error message and exit the programm
 * \param *message message to display
 */
void socket_error_exit(char *message)
{
#ifdef _WIN32
	printf("%s: %d\n", message, WSAGetLastError());
	//debug(stderr);
#else
	printf("%s: %s\n", message, strerror(errno));
	//debug(stderr);
#endif

	exit(EXIT_FAILURE);
}

void socket_error(char *message)
{
#ifdef _WIN32
	printf(" [SOCKET ERROR] %s: %d\n", message, WSAGetLastError());
	//debug(stderr);
#else
	printf(" [SOCKET ERROR] %s: %s\n", message, strerror(errno));
	//debug(stderr);
#endif

}

/**
 * \fn cleanup(void)
 * \brief clean the socket
 */
void cleanup(void)
{
	OnExit();
#ifdef _WIN32
	WSACleanup();
#else
	/* Nichts zu tun */
#endif
}

/**
 * \fn mtime(void)
 * \brief return the actually time in miliseconds for win and linux
 * \return time in ms
 */

unsigned int mtime(void)
{
#ifdef _WIN32
	__int64 freq, value, value2;

	QueryPerformanceFrequency((LARGE_INTEGER*) &freq);
	QueryPerformanceCounter((LARGE_INTEGER*) &value);

	value2 = (value * 1000) / freq;

	unsigned int ms = (unsigned int) (value2 & 0xffffffff);
	return ms;
#else
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return (unsigned int)(tv.tv_sec*1000 + (tv.tv_usec / 1000));
#endif
}

/**
 * \fn void udp_send(int socket, unsigned char *data, int length, struct sockaddr_in *client)
 * \brief send a message over a specific socket to a client
 * \param *socket socket to send over
 * \param *data data to send
 * \param length size of *data
 * \param *client sockaddr_in struct to send data to
 */
void udp_send(int socket, unsigned char *data, int length,
		struct sockaddr_in *client)
{
	int rc;

	rc = sendto(socket, (char*) data, length, 0, (struct sockaddr *) client,
			sizeof(*client));

#ifdef _WIN32
	if (rc == SOCKET_ERROR)
		socket_error("sendto() failed");
#else
	if (rc < 0)
	socket_error("sendto() failed");
#endif
}

/**
 * \fn int udp_recieve(int socket, unsigned char *data, int length, struct sockaddr_in *client)
 * \brief Recieves a message on a specicific socket and save (if something recieved) the data
 * \param socket socket to recieve
 * \param *data pointer where the data should be saved
 * \param length max length of *data
 * \param *client pointer where the clientdata (ip, ...) should be saved
 * \return length of read data
 */
int udp_recieve(int socket, unsigned char *data, int length,
		struct sockaddr_in *client)
{
	struct sockaddr_in newclient;
	int len;
	int size;
	len = sizeof(struct sockaddr_in);
	size = recvfrom(socket, (char*) data, length, 0,
			(struct sockaddr *) &newclient, &len);
	*client = newclient;
#ifdef _WIN32
	if (size == SOCKET_ERROR)
	{
		socket_error_exit("recvfrom() failed");
	}
#else
	if (size < 0)
	{
		socket_error_exit("recvfrom() failed");
	}
#endif
	else
	{
		return size;
	}
	return 0;
}

