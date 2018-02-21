#pragma once
#include <mutex>
#include <atomic>
#include <thread>

class RWLock {
public:
    RWLock() {
        flag_.store(0);
    }

    ~RWLock() = default;

    template<class Func>
    void read(Func func) {
        bool succes = false;

        while(!succes){
            int tst_val = flag_.load();
            if((tst_val & 1) == 0){
                succes = flag_.compare_exchange_weak(tst_val, tst_val+2);
            }
            std::this_thread::yield();
        }

        try {
            func();
        } catch(...) {
            flag_ -= 2;
            throw;
        }
        flag_ -= 2;

    }

    template<class Func>
    void write(Func func) {
        int tst_val = 0;
        while(!flag_.compare_exchange_weak(tst_val,1)){
            std::this_thread::yield();
        }
        try {
            func();
        } catch(...) {
            --flag_;
            throw;
        }
        --flag_;
    }

private:
    std::atomic<int> flag_;
    
};
