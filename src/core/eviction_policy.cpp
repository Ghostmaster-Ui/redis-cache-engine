#include "eviction_policy.h"
#include <stdexcept>

namespace cache {

LRUEvictionPolicy::LRUEvictionPolicy(size_t max_size) : max_size_(max_size) {}

void LRUEvictionPolicy::touch(const std::string& key) {
    auto it = map_.find(key);
    if (it == map_.end()) return;
    order_.erase(it->second);
    order_.push_front(key);
    it->second = order_.begin();
}

void LRUEvictionPolicy::insert(const std::string& key) {
    if (map_.count(key)) {
        touch(key);
        return;
    }
    order_.push_front(key);
    map_[key] = order_.begin();
}

void LRUEvictionPolicy::remove(const std::string& key) {
    auto it = map_.find(key);
    if (it == map_.end()) return;
    order_.erase(it->second);
    map_.erase(it);
}

std::string LRUEvictionPolicy::evict() {
    if (order_.empty())
        throw std::runtime_error("Nothing to evict");
    std::string lru_key = order_.back();
    order_.pop_back();
    map_.erase(lru_key);
    return lru_key;
}

bool LRUEvictionPolicy::is_full() const {
    return map_.size() >= max_size_;
}

} // namespace cache