#ifndef BOT_UDP_TEMPERATURE
#define BOT_UDP_TEMPERATURE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

enum PowerSupply
{
	ETHERNET,
	BATTERY,
};

// TODO: Add checksum field
// FIXME: More precise temperature
struct TemperatureLog
{
	time_t time_marker;
	int temperature;
	enum PowerSupply power_supply;
	uint8_t id;
};

struct TemperatureLog temperature_log_create(int, enum PowerSupply, time_t);

char* temperature_log_generate(struct TemperatureLog*);

// Random PowerSupply
enum PowerSupply power_supply_generate();

// Random temperature in range [20, 120]
int temperature_generate();

char* power_supply_name(enum PowerSupply);

#endif
