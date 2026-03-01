#pragma once
#include <string>
#include <unordered_map>
#include <mutex>
#include "eviction_policy.h"

namespace cache {

struct CacheEntry {
    std::string value;
};

class CacheStore {
public:
    explicit CacheStore(size_t max_size);

    bool set(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string& value_out);
    bool del(const std::string& key);
    size_t size() const;

private:
    size_t max_size_;
    std::unordered_map<std::string, CacheEntry> store_;
    LRUEvictionPolicy lru_;
    mutable std::mutex mutex_;
};

} // namespace cache