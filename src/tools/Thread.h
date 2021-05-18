#pragma once
#include <thread>
#include <memory>
#include <functional>
#include "common/ErrCode.h"
#include "common/Marcos.h"
#include "task/Task.h"

using namespace std;

class ThreadPool;
class Thread {
public:
    Thread(ThreadPool* pool_ptr) : pool_ptr_(pool_ptr) {
        stopped_ = false;
        is_initialized_ = false;
        thread_.reset(new thread(&Thread::run, this));  
    }

    ~Thread() {
        cout << "thread dealloc...." << endl;
        stopped_ = true;
        cv_.notify_one();
        thread_->join();
        cout << "thread dealloc done" << endl;

    }

    void activate() {
        cout << "thread activate" << endl;
        cv_.notify_one();
    }

    bool isInitialized() {
        return is_initialized_;
    }

    void set_task(const TaskPtr& task_ptr) {
        task_ptr_ = task_ptr;
    }

public:
    void run();

    void stop() {
        stopped_ = true;
    }

private:
    shared_ptr<thread> thread_;
    condition_variable cv_;
    TaskPtr task_ptr_;
    ThreadPool* pool_ptr_;
    bool stopped_;
    atomic<bool> is_initialized_;
};
DECLARE_CLASS_POINT_TYPE(Thread);
