cmake_minimum_required(VERSION 3.15)

project(Mini-Redis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_executable(MiniRedis
    main.cpp
    KVDatabase.cpp
    Server.cpp
    Session.cpp
)

target_link_libraries(MiniRedis PRIVATE 
    Boost::boost 
    Threads::Threads
)
