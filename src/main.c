#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include "temperature.h"

int main(int argc, char* argv[])
{
	if (argc < 6)
	{
		printf("[Error] not enough parameters!\n");
		return -1;
	}

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
		char* log = temperature_log_generate(&temperature_log);
		printf("%s\n", log);
		free(log);
		sleep(log_delay);
	}

	return 0;
}
