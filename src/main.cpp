#include <iostream>
#include "core/cache_store.h"
#include "core/consistent_hash.h"
#include "network/server.h"

int main() {
    // Test cache store
    cache::CacheStore store(100);
    store.set("name", "Advit");
    store.set("project", "redis-cache-engine");

    std::string val;
    if (store.get("name", val))
        std::cout << "name: " << val << std::endl;
    if (store.get("project", val))
        std::cout << "project: " << val << std::endl;
    store.del("name");
    if (!store.get("name", val))
        std::cout << "name was deleted successfully" << std::endl;
    std::cout << "Cache size: " << store.size() << std::endl;

    // Test consistent hash ring
    std::cout << "\n--- Consistent Hash Ring ---" << std::endl;
    cache::ConsistentHash ring(100);
    ring.add_node("node-1");
    ring.add_node("node-2");
    ring.add_node("node-3");
    ring.add_node("node-4");

    std::vector<std::string> keys = {
        "user:1", "user:2", "user:3",
        "session:abc", "session:xyz",
        "cache:item1", "cache:item2"
    };
    for (const auto& key : keys)
        std::cout << key << " -> " << ring.get_node(key) << std::endl;

    // Start TCP server
    std::cout << "\n--- Starting Cache Server ---" << std::endl;
    cache::Server server(6379, 1000);
    server.start();

    return 0;
}