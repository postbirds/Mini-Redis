cmake_minimum_required(VERSION 3.15)

project(Mini-Redis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_executable(MiniRedis
    src/main.cpp
    src/KVDatabase.cpp
    src/Server.cpp
    src/Session.cpp
)

target_include_directories(MiniRedis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(MiniRedis PRIVATE 
    Boost::boost 
    Threads::Threads
)
