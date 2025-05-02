#include "udp.h"

struct Server* server_init(const char* ip, unsigned int port)
{
	int sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sfd == -1)
	{
		perror("[Error] Socket create failed");
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

	struct Server* server = malloc(sizeof(struct Server));
	server->sfd = sfd;
	server->addr = server_addr;

	return server;
}

int server_socket_bind(struct Server* server)
{
	socklen_t len = sizeof(server->addr);
	if (bind(server->sfd, (struct sockaddr*)&server->addr, len) == -1)
	{
		perror("[Error] Socket bind failed");
		return -1;
	}

	return 0;
}

void server_destroy(struct Server* server)
{
	close(server->sfd);
	free(server);
}
