#include "client.h"

int main(int argc, char* argv[])
{
	Client* client = client_init(argc, argv);
	if (client == NULL)
	{
		return -1;
	}

	if (client_run(client) == -1)
	{
		client_destroy(client);
		return -1;
	}

	client_destroy(client);

	return 0;
}
