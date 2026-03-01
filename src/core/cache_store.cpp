#include "cache_store.h"

namespace cache {

CacheStore::CacheStore(size_t max_size) 
    : max_size_(max_size), lru_(max_size) {}

bool CacheStore::set(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (lru_.is_full() && store_.find(key) == store_.end()) {
        std::string evicted = lru_.evict();
        store_.erase(evicted);
    }
    store_[key] = { value };
    lru_.insert(key);
    return true;
}

bool CacheStore::get(const std::string& key, std::string& value_out) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = store_.find(key);
    if (it == store_.end()) return false;
    lru_.touch(key);
    value_out = it->second.value;
    return true;
}

bool CacheStore::del(const std::string& key) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!store_.count(key)) return false;
    lru_.remove(key);
    store_.erase(key);
    return true;
}

size_t CacheStore::size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return store_.size();
}

} // namespace cache