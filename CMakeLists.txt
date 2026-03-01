cmake_minimum_required(VERSION 3.16)
project(RedisCacheEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

add_executable(cache_server
    src/main.cpp
    src/core/cache_store.cpp
    src/core/eviction_policy.cpp
    src/core/consistent_hash.cpp
    src/network/server.cpp
    src/network/protocol.cpp
    src/network/connection_pool.cpp
    src/distributed/node_manager.cpp
    src/distributed/replication.cpp
)

target_include_directories(cache_server PRIVATE src)
target_link_libraries(cache_server Threads::Threads)
