cmake_minimum_required(VERSION 3.15)

project(Mini-Redis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(GTest CONFIG REQUIRED)

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

# Test
add_executable(test_kvdatabase
    tests/test_kvdatabase.cpp
    src/KVDatabase.cpp
)
target_include_directories(test_kvdatabase PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test_kvdatabase PRIVATE 
    Boost::boost 
    Threads::Threads
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_kvdatabase)
