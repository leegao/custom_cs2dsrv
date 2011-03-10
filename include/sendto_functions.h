/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef SENDTO_FUNCTIONS_H_
#define SENDTO_FUNCTIONS_H_

#include "main.h"
void SendToPlayer(unsigned char *message, int length, int id, int reliable,
		int writesocket);
void SendToAll(unsigned char *message, int length, int reliable,
		int writesocket);
void SendToTeam(unsigned char *message, int length, int reliable, int team,
		int writesocket);
void SendToAllOther(int id, unsigned char *message, int length, int reliable,
		int writesocket);

// A priority queue for scheduling
typedef struct {
	void* data;
	long long cost;
} pqnode;

typedef struct {
	pqnode q[1000];
	int n;
} pq;

// Macro for queue initialization
#define INIT_QUEUE(q) ((q)->n = 0)
void init_queue(pq* q); // checks for null pointers and etc
void push(pq* q, void* data, long cost); // enqueue, lowest cost comes out first
void* pop(pq* q); // dequeue
int empty(pq* q);
int contains(pq*, void* data);
void* find_cost(pq*, long cost);
pqnode* peek(pq*);

#endif /* SENDTO_FUNCTIONS_H_ */
