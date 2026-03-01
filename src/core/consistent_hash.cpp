#include "consistent_hash.h"
#include <stdexcept>
#include <functional>

namespace cache {

ConsistentHash::ConsistentHash(int virtual_nodes) 
    : virtual_nodes_(virtual_nodes) {}

void ConsistentHash::add_node(const std::string& node) {
    for (int i = 0; i < virtual_nodes_; i++) {
        std::string vnode = node + "#" + std::to_string(i);
        ring_[hash(vnode)] = node;
    }
}

void ConsistentHash::remove_node(const std::string& node) {
    for (int i = 0; i < virtual_nodes_; i++) {
        std::string vnode = node + "#" + std::to_string(i);
        ring_.erase(hash(vnode));
    }
}

std::string ConsistentHash::get_node(const std::string& key) const {
    if (ring_.empty())
        throw std::runtime_error("No nodes in ring");
    uint32_t h = hash(key);
    auto it = ring_.lower_bound(h);
    if (it == ring_.end())
        it = ring_.begin();
    return it->second;
}

bool ConsistentHash::empty() const {
    return ring_.empty();
}

uint32_t ConsistentHash::hash(const std::string& key) const {
    uint32_t hash = 2166136261u;
    for (char c : key) {
        hash ^= static_cast<uint32_t>(c);
        hash *= 16777619u;
    }
    return hash;
}

} // namespace cache