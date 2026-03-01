#pragma once
#include <string>
#include <list>
#include <unordered_map>

namespace cache {

class LRUEvictionPolicy {
public:
    explicit LRUEvictionPolicy(size_t max_size);

    void touch(const std::string& key);
    void insert(const std::string& key);
    void remove(const std::string& key);
    std::string evict();
    bool is_full() const;

private:
    size_t max_size_;
    std::list<std::string> order_;
    std::unordered_map<std::string, std::list<std::string>::iterator> map_;
};

} // namespace cache