#ifndef BOT_UDP_SERVER_SERVER
#define BOT_UDP_SERVER_SERVER

#include <stdio.h>
#include "core/net_socket.h"
#include "core/temperature_log.h"

typedef NetSocket* Server;

Server server_init(const char*, unsigned int);
void server_run(Server);
void server_destroy(Server);

#endif
