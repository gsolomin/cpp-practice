#pragma once

#include <vector>
#include <thread>
#include <iterator>

const int kNumberOfThreads = 8;

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

    std::vector<T> tmp_results;
    tmp_results.resize(kNumberOfThreads);

    std::fill(tmp_results.begin(),tmp_results.end(),initial_value);

    if(length > 2*kNumberOfThreads){
        std::vector<std::thread> threads;

        for(int i =0; i < kNumberOfThreads; ++i){
            threads.emplace_back(reduceImpl<RandomAccessIterator,T,Func>,
                                 first+length*i/kNumberOfThreads, first+length*(i+1)/kNumberOfThreads, func, &tmp_results[i]);
        }

        for(auto&& thr : threads) {
            thr.join();
        }

        while(tmp_results.size() != 1){
            result = func(tmp_results.back(),tmp_results[tmp_results.size()-2]);
            tmp_results.resize(tmp_results.size()-2);
            tmp_results.push_back(result);

        }
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
