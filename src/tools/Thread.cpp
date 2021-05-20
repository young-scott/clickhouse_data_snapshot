#include <iostream>
#include <memory>
#include <condition_variable>
#include "tools/Thread.h"
#include "tools/ThreadPool.h"
static mutex mtx;

void Thread::run() {
    is_initialized_ = true;
    unique_lock<mutex> lck(mtx);
    while(!stopped_) {
        cout << "thread is waiting..." << endl;
        cv_.wait(lck);
        if (stopped_) {
            cout << "thread is stopped" << endl;
            return;
        }
        cout << "new job comming!" << endl;

        if (task_ptr_) {
            task_ptr_->run();
        }

        pool_ptr_->enqueue(this);
    }
}
