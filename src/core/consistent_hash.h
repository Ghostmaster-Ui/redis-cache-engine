#pragma once
#include <string>
#include <map>
#include <vector>

namespace cache {

class ConsistentHash {
public:
    explicit ConsistentHash(int virtual_nodes = 100);

    void add_node(const std::string& node);
    void remove_node(const std::string& node);
    std::string get_node(const std::string& key) const;
    bool empty() const;

private:
    int virtual_nodes_;
    std::map<uint32_t, std::string> ring_;

    uint32_t hash(const std::string& key) const;
};

} // namespace cache