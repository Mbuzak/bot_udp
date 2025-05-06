#include "server.h"

int main(int argc, char* argv[])
{
	const char* ip = "127.0.0.1";
	unsigned int port = 5000;

	Server server = server_init(ip, port);
	if (server == NULL)
	{
		return -1;
	}

	server_run(server);
	server_destroy(server);

	return 0;
}
