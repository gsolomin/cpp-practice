#include "gtest/gtest.h"
#include <algorithm>
#include <vector>
#include <numeric>
#include "commons.h"
#include "reduce.h"


TEST(Correctness, Empty) {
    std::vector<int> values{1, 2, 3};
    ASSERT_EQ(6, reduce(values.begin(), values.end(), 0, [](int sum, int cur) {
        return sum + cur;
    }));

    std::vector<int> empty;
    ASSERT_EQ(0, reduce(empty.begin(), empty.end(), 0, Summator<int>()));

    std::vector<int> one{1};
    ASSERT_EQ(1, reduce(one.begin(), one.end(), 0, Summator<int>()));

    std::vector<int> two{1, 2};
    ASSERT_EQ(3, reduce(two.begin(), two.end(), 0, Summator<int>()));
}

std::vector<uint32_t> generate(size_t size){
    std::vector<uint32_t> v;

    for(size_t i=1;i<size;++i){
        v.push_back(i);
    }
    return v;
}

TEST(Correctness, SimpleTest) {
    std::vector<uint32_t> lst(gen_test(1000));

    auto func = [](uint32_t cur, uint32_t next) {
        return cur * next;
    };
    ASSERT_EQ(std::accumulate(lst.begin(), lst.end(), 1, func),
              reduce(lst.begin(), lst.end(), 1, func));

    auto v = generate(10);
    ASSERT_EQ(std::accumulate(v.begin(), v.end(), 1, func),
              reduce(v.begin(), v.end(), 1, func));
}
