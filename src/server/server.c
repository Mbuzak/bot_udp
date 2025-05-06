#include "server.h"

Server server_init(const char* ip, unsigned int port)
{
	NetSocket* net_socket = net_socket_init(ip, port);
	if (net_socket == NULL)
	{
		return NULL;
	}

	if (net_socket_bind(net_socket) == -1)
	{
		return NULL;
	}

	return net_socket;
}

void server_run(Server server)
{
	int quit = 0;
	while (!quit)
	{
		TemperatureLog temperature_log;
		socklen_t len = sizeof(server->addr);
		struct sockaddr_in client_addr;

		if (recvfrom(server->fd, (TemperatureLog*)&temperature_log,
			sizeof(TemperatureLog), 0, (struct sockaddr*)&client_addr,
			&len) <= 0)
		{
			perror("[Warning] Message not received");
		}

		char* log = temperature_log_generate(&temperature_log);
		printf("%s", log);
	}
}

void server_destroy(Server server)
{
	net_socket_destroy(server);
}
