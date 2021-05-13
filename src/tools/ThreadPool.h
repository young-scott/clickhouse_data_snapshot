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
    static shared_ptr<ThreadPool> instance() {
        if (!instance_) {
            instance_.reset(new ThreadPool());
        }
        return instance_;
    }

    void set_max_thread_size(size_t thread_size) {
        cout << "set max thread size : [" << thread_size << "]" << endl;
        max_thread_size_ = thread_size;
    }

    void enqueue(const ThreadPtr& thread) {
        threads_.push_back(thread);
        --running;
    }

    ErrCode process(const vector<TaskPtr>& tasks);
        

private:
    ErrCode initial() {
        return ErrCode::ERROR_NONE;
    }

private:
    static shared_ptr<ThreadPool> instance_;
    bool stopped_;
    bool ready_;

    list<ThreadPtr> threads_;
    atomic<int> running;
    mutex queue_mtx_;


    size_t max_thread_size_;
    size_t thread_size_;
};
DECLARE_CLASS_POINT_TYPE(ThreadPool);