#include "net_socket.h"

NetSocket* net_socket_init(const char* ip, unsigned int port)
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1)
	{
		perror("[Error] Network socket create failed");
		return NULL;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
	{
		perror("[Error] IP address convert from text to binary failed");
		return NULL;
	}

	NetSocket* net_socket = malloc(sizeof(NetSocket));
	net_socket->fd = fd;
	net_socket->addr = server_addr;

	return net_socket;
}

int net_socket_bind(NetSocket* net_socket)
{
	socklen_t len = sizeof(net_socket->addr);
	if (bind(net_socket->fd, (struct sockaddr*)&net_socket->addr, len) == -1)
	{
		perror("[Error] Network socket bind failed");
		return -1;
	}

	return 0;
}

void net_socket_destroy(NetSocket* net_socket)
{
	close(net_socket->fd);
	free(net_socket);
}
