#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "temperature.h"
#include "udp.h"

struct TemperatureLog temperature_log;

void* temperature_log_send(void* args)
{
	struct SendArgs* send_args = args;
	struct Server* server = send_args->server;
	socklen_t len = sizeof(server->addr);
	int quit = 0;

	while (!quit)
	{
		int8_t temperature = temperature_generate();
		uint8_t power_supply = power_supply_generate();
		temperature_log = temperature_log_create(temperature, power_supply, send_args->time_start);

		if (sendto(server->sfd, &temperature_log, sizeof(struct TemperatureLog),
			0, (struct sockaddr*)&server->addr, len) == -1)
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

int main(int argc, char* argv[])
{
	pthread_t thread_log;
	pthread_t thread_send;

	if (argc < 6)
	{
		printf("[Error] Not enough parameters\n");
		return -1;
	}

	const char* ip = argv[1];
	unsigned int port = atoi(argv[2]);
	unsigned int send_delay = atoi(argv[3]);
	unsigned int log_delay = atoi(argv[4]);
	const char* log_path = argv[5];

	struct Server* server = server_init(ip, port);
	if (server == NULL)
	{
		return -1;
	}

	time_t time_start = time(NULL);
	srand(time_start);

	struct LogArgs log_args = {.path = log_path, .delay = log_delay};
	if (pthread_create(&thread_log, NULL, &temperature_log_save, &log_args) != 0)
	{
		printf("[Error]\n");
		return -1;
	}

	struct SendArgs send_args = {.server = server, .time_start = time_start, .delay = send_delay};
	if (pthread_create(&thread_send, NULL, &temperature_log_send, &send_args) != 0)
	{
		printf("[Error] Send error\n");
		return -1;
	}

	pthread_join(thread_log, NULL);
	pthread_join(thread_send, NULL);

	pthread_exit(NULL);
	server_destroy(server);

	return 0;
}
