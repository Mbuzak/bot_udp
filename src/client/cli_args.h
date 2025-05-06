#ifndef BOT_UDP_CLI_ARGS
#define BOT_UDP_CLI_ARGS

#include <stdlib.h>

// Command-line interface arguments
typedef struct
{
	const char* ip;
	unsigned int port;
	unsigned int send_delay;
	unsigned int log_delay;
	const char* log_path;
} CliArgs;

CliArgs cli_args_init(int, char**);

#endif
