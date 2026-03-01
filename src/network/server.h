#pragma once
#include <string>
#include <thread>
#include <atomic>
#include "core/cache_store.h"
#include "core/consistent_hash.h"
#include "network/protocol.h"

namespace cache {

class Server {
public:
    Server(int port, size_t cache_size);
    ~Server();

    void start();
    void stop();

private:
    int port_;
    int server_fd_;
    std::atomic<bool> running_;
    CacheStore store_;
    ConsistentHash ring_;

    void accept_loop();
    void handle_client(int client_fd);
    Response process_request(const Request& req);
};

} // namespace cache