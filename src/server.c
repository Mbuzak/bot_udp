#include <stdio.h>
#include "temperature.h"
#include "udp.h"

int main(int argc, char* argv[])
{
	const char* ip = "127.0.0.1";
	unsigned int port = 5000;

	struct Server* server = server_init(ip, port);
	if (server == NULL)
	{
		return -1;
	}

	if (server_socket_bind(server) == -1)
	{
		return -1;
	}

	int quit = 0;
	while (!quit)
	{
		struct TemperatureLog temperature_log;
		socklen_t len = sizeof(server->addr);
		struct sockaddr_in client_addr;

		if (recvfrom(server->sfd, (struct TemperatureLog*)&temperature_log,
			sizeof(struct TemperatureLog), 0, (struct sockaddr*)&client_addr,
			&len) <= 0)
		{
			perror("[Warning] Message not received");
		}

		char* log = temperature_log_generate(&temperature_log);
		printf("%s", log);
	}

	server_destroy(server);

	return 0;
}
