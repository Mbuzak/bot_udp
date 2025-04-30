#include "temperature.h"

struct TemperatureLog temperature_log_create(int temperature, enum PowerSupply power_supply, time_t time_start)
{
	struct TemperatureLog temperature_log;

	temperature_log.temperature = temperature;

	static uint8_t id = 0;
	temperature_log.id = ++id;

	temperature_log.power_supply = power_supply;

	time_t time_marker = time(NULL) - time_start;
	temperature_log.time_marker = time_marker;

	return temperature_log;
}

char* temperature_log_generate(struct TemperatureLog* temperature_log)
{
	char* log = malloc(sizeof(char) * 64);

	strcpy(log, "[Info] ");
	char id[4];
	strcat(log, "Id: ");
	sprintf(id, "%d", temperature_log->id);
	strcat(log, id);

	strcat(log, " Time: ");
	char time_marker[4];
	sprintf(time_marker, "%ld", temperature_log->time_marker);
	strcat(log, time_marker);

	char temperature[3];
	sprintf(temperature, "%d", temperature_log->temperature);
	strcat(log, " Temperature: ");
	strcat(log, temperature);

	strcat(log, " Power supply: ");
	strcat(log, power_supply_name(temperature_log->power_supply));

	return log;
}

enum PowerSupply power_supply_generate()
{
	int choice = rand() % 2;
	if (choice == 0)
	{
		return ETHERNET;
	}

	return BATTERY;
}

int temperature_generate()
{
	int temperature = (rand() % 101) + 20;
	return temperature;
}

char* power_supply_name(enum PowerSupply power_supply)
{
	if (power_supply == ETHERNET)
	{
		return "Ethernet";
	}
	else if (power_supply == BATTERY)
	{
		return "Battery";
	}
	
	return "Not found";
}
