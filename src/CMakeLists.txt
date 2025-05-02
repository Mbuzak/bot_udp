add_executable(${PROJECT_NAME} main.c temperature.c udp.c)
add_executable(server server.c temperature.c udp.c)
