#include "lru_cache.h"

LruCache::LruCache(size_t max_size) : max_size_(max_size) {}

void LruCache::Set(const std::string& key, const std::string& value) {
    if(cache_.count(key) > 0) {
        lru_.remove(cache_.find(key));
    }

    cache_[key] = value;
    lru_.push_front(cache_.find(key));

    if(cache_.size() > max_size_){
        auto it = lru_.back();
        lru_.pop_back();
        cache_.erase(it);
    }
}

bool LruCache::Get(const std::string& key, std::string* value) {
    if(cache_.count(key) == 0) return false;

    *value = cache_[key];

    lru_.remove(cache_.find(key));
    lru_.push_front(cache_.find(key));

    return true;
}
