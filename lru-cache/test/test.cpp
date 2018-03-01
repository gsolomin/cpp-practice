#include "lru_cache.h"
#include <gtest/gtest.h>


TEST(Set_and_get, LruCache) {
    LruCache cache(10);

    std::string value;

    cache.Set("a", "1");
    cache.Set("b", "2");
    cache.Set("c", "3");

    ASSERT_TRUE(cache.Get("a", &value));
    ASSERT_TRUE("1" == value);
    ASSERT_TRUE(cache.Get("b", &value));
    ASSERT_TRUE("2" == value);
    ASSERT_TRUE(cache.Get("c", &value));
    ASSERT_TRUE("3" == value);

    ASSERT_FALSE(cache.Get("d", &value));

    cache.Set("c", "4");
    ASSERT_TRUE(cache.Get("c", &value));
    ASSERT_TRUE("4" == value);
}

TEST(Eviction, LruCache) {
    LruCache cache(2);
    std::string value;

    cache.Set("a", "1");
    cache.Set("b", "2");
    cache.Set("c", "3");

    ASSERT_FALSE(cache.Get("a", &value));
    ASSERT_TRUE(cache.Get("b", &value));
    ASSERT_TRUE(cache.Get("c", &value));

    cache.Set("b", "4");
    cache.Set("c", "5");
    cache.Set("b", "6");

    cache.Set("e", "7");
    ASSERT_FALSE(cache.Get("c", &value));
    ASSERT_TRUE(cache.Get("b", &value));
    ASSERT_TRUE(cache.Get("e", &value));

    cache.Get("b", &value);
    cache.Set("f", "8");
    ASSERT_FALSE(cache.Get("e", &value));
    ASSERT_TRUE(cache.Get("b", &value));
    ASSERT_TRUE(cache.Get("f", &value));
}
