#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "temperature.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));

	time_t time_start = time(NULL);

	int i = 0;
	int quit = 0;
	while (!quit)
	{
		int temperature = temperature_generate();
		enum PowerSupply power_supply = power_supply_generate();
		struct TemperatureLog temperature_log = temperature_log_create(temperature, power_supply, time_start);
		char* log = temperature_log_generate(&temperature_log);
		printf("%s\n", log);
		free(log);
		sleep(1);

		if (++i >= 2)
		{
			quit = 1;
		}
	}

	return 0;
}
