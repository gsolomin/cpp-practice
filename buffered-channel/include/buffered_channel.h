#pragma once

#include <utility>
#include <cmath>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size): size_(size) {
    	isClosed.store(false);
        currentsize_ = 0;
    }
    void send(const T& value) {
    	if(isClosed.load()){
    		throw std::runtime_error("Channel closed"); 
    	}
    	std::unique_lock<std::mutex> lock(mutex_);
    	cv_.wait(lock, [this](){
    			return currentsize_ < size_ || isClosed.load();
    		});

    	if(isClosed.load()){
    		throw std::runtime_error("Channel closed"); 
    	}
    	channel_.push(value);
        ++currentsize_;
    	cv_.notify_one();
    }

    std::pair<T, bool> recv() {
    	std::unique_lock<std::mutex> lock(mutex_);
    	cv_.wait(lock, [this](){
    			return currentsize_ > 0 || isClosed.load();
    		});
    	if(isClosed.load() && currentsize_ == 0){
    		return std::make_pair(T(), false);
    	}
    	auto retval = std::make_pair(channel_.front(),true);
    	channel_.pop();
        --currentsize_;
    	cv_.notify_one();
        return retval;
    }
    void close() {
    	isClosed.store(true);
    	cv_.notify_all();
    }

private:
	size_t size_;
    size_t currentsize_;
	std::queue<T> channel_;
	std::mutex mutex_;
    std::condition_variable cv_;
	std::atomic<bool> isClosed;
};
