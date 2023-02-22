cmake_minimum_required(VERSION 3.23)
project(InnoUni_NetworksCourse_labs C)

set(CMAKE_C_STANDARD 99)

add_executable(week5_server week5/server.c)
add_executable(week5_client week5/client.c)