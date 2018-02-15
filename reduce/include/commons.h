#pragma once

#include <vector>

template<class T>
class Summator {
public:
    T operator()(const T &sum, const T &cur_value) const;
};

template<class T>
class Multiplier {
public:
    T operator()(const T &mul, const T &cur_value) const;
};

std::vector<uint32_t> gen_test(int size);