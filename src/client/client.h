#ifndef BOT_UDP_CLIENT_CLIENT
#define BOT_UDP_CLIENT_CLIENT

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "cli_args.h"
#include "core/temperature_log.h"
#include "core/net_socket.h"

typedef struct
{
	CliArgs cli_args;
	NetSocket* net_socket;
	time_t app_start;
} Client;

static TemperatureLog temperature_log;

Client* client_init(int, char**);
int client_run(Client*);
void client_destroy(Client*);

void* temperature_log_send(void*);
void* temperature_log_save(void*);

#endif
