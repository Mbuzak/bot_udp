#ifndef BOT_UDP_CORE_NET_SOCKET
#define BOT_UDP_CORE_NET_SOCKET

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Network socket
typedef struct
{
	// file descriptor
	int fd;
	struct sockaddr_in addr;
} NetSocket;

struct SendArgs
{
	NetSocket* net_socket;
	time_t time_start;
	unsigned int delay;
};

NetSocket* net_socket_init(const char*, unsigned int);

int net_socket_bind(NetSocket*);

void net_socket_destroy(NetSocket*);

#endif
