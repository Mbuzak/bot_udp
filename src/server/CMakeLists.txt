add_executable(server main.c server.c)

target_link_libraries(server PRIVATE core)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
