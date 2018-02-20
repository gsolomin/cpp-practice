#pragma once

#include <utility>
#include <mutex>
#include <exception>
#include <condition_variable>
#include <atomic>

template<class T>
class UnbufferedChannel {
public:
    UnbufferedChannel(){
        isclosed_.store(false);
    }

    void send(const T& value) {
        std::unique_lock<std::mutex> lock(mutex_);

        sendcv_.wait(lock, [this](){
            return !buffer_ || isclosed_.load();
        });

        if(isclosed_.load()){
            throw std::runtime_error("Channel closed");
        }
        
        buffer_ = std::make_unique<T>(value);
        recvcv_.notify_one();
        sendcv_.wait(lock, [this](){
            return !buffer_ || isclosed_.load();
        });
        sendcv_.notify_one();
    }

    std::pair<T, bool> recv() {
        std::unique_lock<std::mutex> lock(mutex_);
        recvcv_.wait(lock, [this](){
            return buffer_ || isclosed_.load();
        });

        if(isclosed_.load() && !buffer_){
            return std::make_pair(T(), false);
        }

        auto retval = std::make_pair(*buffer_,true);
        buffer_.release();
        sendcv_.notify_all();
        return retval;
    }

    void close() {
        isclosed_.store(true);
        sendcv_.notify_all();
        recvcv_.notify_all();
    }

private:
    std::unique_ptr<T> buffer_;
    std::mutex mutex_;
    std::condition_variable sendcv_, recvcv_;
    std::atomic<bool> isclosed_;
};