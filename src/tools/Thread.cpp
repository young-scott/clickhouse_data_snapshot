#include <iostream>
#include <memory>
#include "tools/Thread.h"
#include "tools/ThreadPool.h"
static mutex mtx;

void Thread::run() {
    while(!stopped_) {
        unique_lock<mutex> lck(mtx);
        while (cv_.wait_for(lck,chrono::seconds(1)) == cv_status::timeout) {
            cout << '.' << endl;
            if (stopped_) {
                cout << "thread is stopped" << endl;
                return;
            }
        }
        if (task_ptr_) {
            task_ptr_->run();
        }
        pool_ptr_->enqueue(ThreadPtr(this));
    }
}
