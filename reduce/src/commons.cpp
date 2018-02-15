#include "commons.h"
#include <vector>
#include <random>

template<class T>
T Summator<T>::operator()(const T& sum, const T& cur_value) const {
    return sum + cur_value;
}

template class Summator<int>;

template<class T>
T Multiplier<T>::operator()(const T& mul, const T& cur_value) const {
    return mul * cur_value;
}

template class Multiplier<int>;

std::vector<uint32_t> gen_test(int size) {
    std::vector<uint32_t> result(size);
    static std::mt19937 gen(7347475);
    for(auto& cur : result) {
        cur = gen();
        if (!cur)
            ++cur;
    }
    return result;
}
