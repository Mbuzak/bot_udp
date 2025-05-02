#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "temperature.h"
#include "udp.h"

int main(int argc, char* argv[])
{
	if (argc < 6)
	{
		printf("[Error] Not enough parameters\n");
		return -1;
	}

	const char* ip = argv[1];
	unsigned int port = atoi(argv[2]);
	unsigned int data_send_delay = atoi(argv[3]);
	unsigned int log_delay = atoi(argv[4]);
	const char* log_path = argv[5];

	struct Server* server = server_init(ip, port);
	if (server == NULL)
	{
		return -1;
	}

	time_t time_start = time(NULL);
	srand(time_start);

	int quit = 0;
	while (!quit)
	{
		int8_t temperature = temperature_generate();
		uint8_t power_supply = power_supply_generate();
		struct TemperatureLog temperature_log =
			temperature_log_create(temperature, power_supply, time_start);

		if (temperature_log_save(&temperature_log, log_path) == -1)
		{
			perror("[Warning] File could not be open");
		}

		socklen_t len = sizeof(server->addr);
		if (sendto(server->sfd, &temperature_log, sizeof(struct TemperatureLog),
			0, (struct sockaddr*)&server->addr, len) == -1)
		{
			perror("[Warning] Message not send");
		}

		sleep(log_delay);
	}

	server_destroy(server);

	return 0;
}
