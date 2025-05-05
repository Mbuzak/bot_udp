cmake_minimum_required(VERSION 3.28)
project(bot_udp VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

add_subdirectory(src)
