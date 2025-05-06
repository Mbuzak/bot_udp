#include "cli_args.h"

CliArgs cli_args_init(int argc, char** argv)
{
	CliArgs cli_args =
	{
		.ip = "127.0.0.1",
		.port = 5000,
		.send_delay = 2,
		.log_delay = 5,
		.log_path = "log.txt"
	};

	if (argc < 6)
	{
		return cli_args;
	}

	cli_args.ip = argv[1];
	cli_args.port = atoi(argv[2]);
	cli_args.log_delay = atoi(argv[3]);
	cli_args.send_delay = atoi(argv[4]);
	cli_args.log_path = argv[5];

	return cli_args;
}
