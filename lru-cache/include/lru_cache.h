#pragma once

#include <list>
#include <string>
#include <unordered_map>

class LruCache {
public:
    LruCache(size_t max_size);

    void Set(const std::string& key, const std::string& value);

    bool Get(const std::string& key, std::string* value);

private:
    size_t max_size_;
    std::unordered_map<std::string,std::string> cache_;
    std::list<std::unordered_map<std::string,std::string>::iterator> lru_;
};
