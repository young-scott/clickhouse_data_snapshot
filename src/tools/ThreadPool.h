#pragma once
#include <thread>
#include <map>
#include <list>
#include <atomic>
#include <iostream>
#include <chrono> 
#include "common/Marcos.h"
#include "common/ErrCode.h"
#include "tools/Thread.h"

class ThreadPool {
public: 
    ThreadPool(size_t thread_size);
    ~ThreadPool();

    void set_max_thread_size(size_t thread_size) {
        cout << "set max thread size : [" << thread_size << "]" << endl;
        max_thread_size_ = thread_size;
    }

    void enqueue(Thread* thread) {
        cout << "enqueue thread" << endl;
        free_threads_.push_back(thread);
    }

    ErrCode process(const vector<TaskPtr>& tasks);
        
private:
    ErrCode initial(size_t thread_size);

private:
    bool stopped_;

    mutex queue_mtx_;
    condition_variable cv_;

    list<Thread*> free_threads_;
    list<Thread*> threads_;
    atomic<size_t> thread_size_;

    size_t max_thread_size_;
    
};
DECLARE_CLASS_POINT_TYPE(ThreadPool);