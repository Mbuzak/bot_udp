#ifndef BOT_UDP_TEMPERATURE_LOG
#define BOT_UDP_TEMPERATURE_LOG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define POWER_SUPPLY_ETHERNET 1
#define POWER_SUPPLY_BATTERY 2
#define LOG_SIZE 128

typedef struct
{
	time_t time_marker;
	int8_t temperature;
	uint8_t power_supply;
	uint8_t id;
	uint8_t checksum;
} TemperatureLog;

struct LogArgs
{
	const char* path;
	unsigned int delay;
};

TemperatureLog temperature_log_create(int8_t, uint8_t, time_t);

char* temperature_log_generate(TemperatureLog*);

// Random PowerSupply
uint8_t power_supply_generate();

// Random temperature in range [20, 120] with precision 0.1
int8_t temperature_generate();

char* power_supply_name(uint8_t);

// Display log and save to file
void* temperature_log_save(void*);

size_t string_length(char*);

#endif
