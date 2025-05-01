#include "temperature.h"

struct TemperatureLog temperature_log_create(int8_t temperature, uint8_t power_supply, time_t time_start)
{
	struct TemperatureLog temperature_log;

	temperature_log.temperature = temperature;

	static uint8_t id = 0;
	temperature_log.id = ++id;

	temperature_log.power_supply = power_supply;

	time_t time_marker = time(NULL) - time_start;
	temperature_log.time_marker = time_marker;

	// generate checksum
	uint8_t sum = temperature + id + time_marker + power_supply;
	temperature_log.checksum = sum;

	return temperature_log;
}

char* temperature_log_generate(struct TemperatureLog* temperature_log)
{
	char* log = malloc(sizeof(char) * 128);

	strcpy(log, "[Info] ");
	char id[4];
	strcat(log, "Id: ");
	sprintf(id, "%d", temperature_log->id);
	strcat(log, id);

	strcat(log, "\tTime: ");
	char time_marker[4];
	sprintf(time_marker, "%ld", temperature_log->time_marker);
	strcat(log, time_marker);

	char temperature[5];
	sprintf(temperature, "%d", temperature_log->temperature);
	strcat(log, "s\tTemperature: ");
	strcat(log, temperature);

	strcat(log, " C\tPower supply: ");
	strcat(log, power_supply_name(temperature_log->power_supply));

	strcat(log, " \tChecksum: ");
	char checksum[4];
	sprintf(checksum, "%d", temperature_log->checksum);
	strcat(log, checksum);

	return log;
}

uint8_t power_supply_generate()
{
	int choice = rand() % 2;
	if (choice == 0)
	{
		return POWER_SUPPLY_ETHERNET;
	}

	return POWER_SUPPLY_BATTERY;
}

int8_t temperature_generate()
{
	int temperature = (rand() % 101) + 20;
	float temperature_precise = (float)(rand() % 10) / 10;
	temperature += temperature_precise >= .5f ? 1 : 0;
	
	return (int8_t)temperature;
}

char* power_supply_name(uint8_t power_supply)
{
	if (power_supply == POWER_SUPPLY_ETHERNET)
	{
		return "Ethernet";
	}
	else if (power_supply == POWER_SUPPLY_BATTERY)
	{
		return "Battery";
	}

	return "Not found";
}
