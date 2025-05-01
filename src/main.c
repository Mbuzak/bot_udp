#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "temperature.h"

#define IP "127.0.0.1"

int main(int argc, char* argv[])
{
	int sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sfd == -1)
	{
		perror("[Error] Socket create failed");
		return -1;
	}

	struct sockaddr_in sad;
	sad.sin_family = AF_INET;
	if (inet_pton(AF_INET, IP, &sad.sin_addr) <= 0)
	{
		perror("[Error] IP address convert from text to binary failed");
		return -1;
	}

	sad.sin_port = htons(5000);
	socklen_t slen = sizeof(sad);

	if (argc < 6)
	{
		printf("[Error] not enough parameters!\n");
		return -1;
	}

	const char* ip_addr = argv[1];
	unsigned int port = atoi(argv[2]);
	int data_send_delay = atoi(argv[3]);
	int log_delay = atoi(argv[4]);
	const char* log_path = argv[5];

	time_t time_start = time(NULL);
	srand(time_start);

	int quit = 0;
	while (!quit)
	{
		int8_t temperature = temperature_generate();
		uint8_t power_supply = power_supply_generate();
		struct TemperatureLog temperature_log = temperature_log_create(temperature, power_supply, time_start);

		if (temperature_log_save(&temperature_log, log_path) == -1)
		{
			printf("[Warning] File could not be open! Errno: %d\n", errno);
		}

		if (sendto(sfd, &temperature_log, sizeof(struct TemperatureLog), 0, (struct sockaddr*)&sad, slen) == -1)
		{
			perror("[Warning] Message not send");
		}

		sleep(log_delay);
	}

	return 0;
}
