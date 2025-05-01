#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "temperature.h"

#define IP "127.0.0.1"
#define SERVER_PORT 5000

int main(int argc, char* argv[])
{
	int sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sfd == -1)
	{
		perror("[Error] Socket create failed");
		return -1;
	}

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	server_addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, IP, &server_addr.sin_addr) <= 0)
	{
		perror("[Error] IP address convert from text to binary failed");
		return -1;
	}

	socklen_t server_addr_len = sizeof(server_addr);
	socklen_t client_addr_len = sizeof(server_addr);
	server_addr.sin_port = htons(SERVER_PORT);
	if (bind(sfd, (struct sockaddr*)&server_addr, server_addr_len) == -1)
	{
		perror("[Error] Socket bind failed");
		return -1;
	}

	int quit = 0;
	while (!quit)
	{
		struct TemperatureLog temperature_log;
		if (recvfrom(sfd, (struct TemperatureLog*)&temperature_log, sizeof(struct TemperatureLog), 0, (struct sockaddr*)&client_addr, &client_addr_len) <= 0)
		{
			perror("[Warning] Message not received");
		}

		char* log = temperature_log_generate(&temperature_log);
		printf("%s", log);
	}

	return 0;
}
