add_executable(${PROJECT_NAME} main.c cli_args.c client.c)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads core)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
