/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#include "sendto_functions.h"

void SendToPlayer(unsigned char *message, int length, int id, int reliable,
		int writesocket)
{
	struct sockaddr_in tempclient;
	tempclient.sin_family = AF_INET;
	tempclient.sin_port = player[id].port;
	tempclient.sin_addr = player[id].ip;
	unsigned char *buffer = malloc(length + 2);
	if (buffer == NULL)
		error_exit("Memory error ( SendToPlayer() )");

	if (reliable == 1)
	{
		unsigned short *pNummer = &player[id].server_nummer;
		memcpy(buffer, pNummer, sizeof(unsigned short));
		player[id].server_nummer += 2;
	}
	else if (reliable == 0)
	{
		player[id].server_nummer--;
		unsigned short *pNummer = &player[id].server_nummer;
		memcpy(buffer, pNummer, sizeof(unsigned short));
		player[id].server_nummer++;
	}
	memcpy(buffer + 2, message, length);
	udp_send(writesocket, buffer, length + 2, &tempclient);

	free(buffer);
}

void SendToAll(unsigned char *message, int length, int reliable,
		int writesocket)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		if (player[i].used == 1 && player[i].joinstatus >= 4)
		{
			SendToPlayer(message, length, i, reliable, writesocket);
		}
	}
}

void SendToTeam(unsigned char *message, int length, int reliable, int team,
		int writesocket)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		if (player[i].used == 1 && player[i].joinstatus >= 4 && player[i].team
				== team)
		{
			SendToPlayer(message, length, i, reliable, writesocket);
		}
	}
}

void SendToAllOther(int id, unsigned char *message, int length, int reliable,
		int writesocket)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		if (player[i].used == 1 && player[i].joinstatus >= 4 && i != id)
		{
			SendToPlayer(message, length, i, reliable, writesocket);
		}
	}
}

// Priority Queue implementation

void init_queue(pq *q){
	if (!q) return perror("Cannot initialize null queues.");
	if (q->n) perror("The current queue is already linked.");
	q->n = 0;
}

// We will implement our PQ using a heap-like structure through a fixed array.
/*
 * Heap invariants:
 * parent -> (index-1)/2
 * child -> 2*index + 1 or 2
 * child.cost is always less than parent.cost
 * */
void push(pq *q, void* data, long long cost){
	// Create a node to work with the data.
	pqnode* x = (pqnode*)malloc(sizeof(pqnode));
	x->data = data;
	x->cost = cost;

	// Traversal indices.
	int prev, next;

	if (q->n > 1000) return perror("The current queue is full, did not add.");
	q->q[(next = q->n++)] = *x;
	prev = (next-1)/2; // heap invariant -> prev node is at (n-1)/2

	while(next > 0 && q->q[next].cost < q->q[prev].cost){ // Heap invariant - child always less
		// Swap
		pqnode cur = q->q[next];
		q->q[next] = q->q[prev];
		q->q[prev] = cur;

		// Re-establish traversal indices
		next = prev; // child
		prev = (next-1)/2; // parent
	}

	// insert the new value
	q->q[next] = *x;
}

int empty(pq *q){
	return !q->n;
}
