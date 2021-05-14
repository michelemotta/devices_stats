cmake_minimum_required(VERSION 3.16)

project(device_stat)

set(CMAKE_CXX_STANDARD 14)

add_library(server
            ./src/Server.cpp
            )

target_include_directories(server PUBLIC ./include)

add_executable( device_stat
                ./src/main.cpp
                ./src/Node.cpp)

target_include_directories(device_stat PUBLIC ./include)

target_link_libraries(device_stat PRIVATE server)