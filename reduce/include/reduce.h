#pragma once

#include <vector>
#include <thread>
#include <iterator>

template<class RandomAccessIterator, class T, class Func>
void reduceImpl(RandomAccessIterator first, RandomAccessIterator last, Func func, T* result) {
    auto cur_value(*result);
    while (first != last)
        cur_value = func(cur_value, *first++);
    *result = cur_value;
}

template<class RandomAccessIterator, class T, class Func>
T reduce(RandomAccessIterator first, RandomAccessIterator last, const T &initial_value, Func func) {
    auto result(initial_value);

    size_t length = std::distance(first, last);

    T tmp_results[] = {initial_value,initial_value,initial_value,initial_value};

    if(length > 4){
        std::vector<std::thread> threads;
        threads.reserve(4);
        for(int i =0; i < 4; ++i){
            threads.emplace_back(reduceImpl<RandomAccessIterator,T,Func>,
                                 first+length*i/4, first+length*(i+1)/4, func, &tmp_results[i]);
        }

        for(int i =0; i < 4; ++i) {
            threads[i].join();
        }

        result =  func(tmp_results[0],
                       func(tmp_results[1],
                            func(tmp_results[2],tmp_results[3])));
    }
    else
    {
        std::thread reducethr(
                reduceImpl<RandomAccessIterator,T,Func>,
                first, last, func, &result);
        reducethr.join();
    }
    return result;
}
