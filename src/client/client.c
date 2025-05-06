#include "client.h"

void* temperature_log_send(void* args)
{
	struct SendArgs* send_args = args;
	NetSocket* net_socket = send_args->net_socket;
	socklen_t len = sizeof(net_socket->addr);
	int quit = 0;

	while (!quit)
	{
		int8_t temperature = temperature_generate();
		uint8_t power_supply = power_supply_generate();
		temperature_log = temperature_log_create(temperature, power_supply, send_args->time_start);

		if (sendto(net_socket->fd, &temperature_log, sizeof(TemperatureLog),
			0, (struct sockaddr*)&net_socket->addr, len) == -1)
		{
			perror("[Warning] Message not send");
		}

		printf("[Info] Send\n");
		sleep(send_args->delay);
	}

	return NULL;
}

void* temperature_log_save(void* args)
{
	struct LogArgs* log_args = args;
	int quit = 0;

	while (!quit)
	{
		char* log = temperature_log_generate(&temperature_log);

		FILE* file_log = fopen(log_args->path, "a");
		if (file_log == NULL)
		{
			perror("[Warning] File could not be open");
			fclose(file_log);
			free(log);

			return NULL;
		}

		size_t size = string_length(log);
		fwrite(log, size, 1, file_log);
		printf("%s", log);

		fclose(file_log);
		free(log);

		sleep(log_args->delay);
	}

	return NULL;
}

Client* client_init(int argc, char** argv)
{
	CliArgs cli_args = cli_args_init(argc, argv);
	NetSocket* net_socket = net_socket_init(cli_args.ip, cli_args.port);
	if (net_socket == NULL)
	{
		return NULL;
	}

	time_t app_start = time(NULL);
	srand(app_start);

	Client* client = malloc(sizeof(Client));
	client->cli_args = cli_args;
	client->net_socket = net_socket;
	client->app_start = app_start;

	return client;
}

int client_run(Client* client)
{
	pthread_t thread_log;
	struct LogArgs log_args = {.path = client->cli_args.log_path, .delay = client->cli_args.log_delay};
	if (pthread_create(&thread_log, NULL, &temperature_log_save, &log_args) != 0)
	{
		printf("[Error] Thread log create failed!\n");
		return -1;
	}

	pthread_t thread_send;
	struct SendArgs send_args = {.net_socket = client->net_socket, .time_start = client->app_start, .delay = client->cli_args.send_delay};
	if (pthread_create(&thread_send, NULL, &temperature_log_send, &send_args) != 0)
	{
		printf("[Error] Thread send create failed!\n");
		return -1;
	}

	pthread_join(thread_log, NULL);
	pthread_join(thread_send, NULL);

	return 0;
}

void client_destroy(Client* client)
{
	pthread_exit(NULL);
	net_socket_destroy(client->net_socket);
	free(client);
}
