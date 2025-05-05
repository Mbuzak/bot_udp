#ifndef BOT_UDP_UDP
#define BOT_UDP_UDP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct Server
{
	// socket file descriptor
	int sfd;
	struct sockaddr_in addr;
};

struct SendArgs
{
	struct Server* server;
	time_t time_start;
	unsigned int delay;
};

struct Server* server_init(const char*, unsigned int);

int server_socket_bind(struct Server*);

void server_destroy(struct Server*);

#endif
