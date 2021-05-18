#include "tools/ThreadPool.h"
ThreadPool::ThreadPool(size_t thread_size) : max_thread_size_(thread_size) {
    stopped_ = false;
}

ThreadPool::~ThreadPool() {
    cout << "thread pool release thread ：[" <<  threads_.size() << "]" << endl;
    free_threads_.clear();
    for (auto thread : threads_) {
        delete thread;
    }
    threads_.clear();
    cout << "thread pool release done" << endl;

}

ErrCode ThreadPool::initial(size_t thread_size) {
    for (size_t i = 0; i < thread_size; ++i) {
        Thread* thread = new Thread(this);
        unique_lock<mutex> lk(queue_mtx_);
        cout << "initial thread ..." << endl;
        if(!cv_.wait_for(lk, 1s,  [thread]{ return thread->isInitialized(); })) {
            cout << "initial thread ..." << endl;
        };
        cout << "initial thread done" << endl;
        threads_.push_back(thread);
    }
    thread_size_ = thread_size;
    free_threads_.insert(free_threads_.end(), threads_.begin(), threads_.end());
    return ErrCode::ERROR_NONE;
}

ErrCode ThreadPool::process(const vector<TaskPtr>& tasks) {
    cout << "receive task size : [" << tasks.size() << "]" << endl;

    /// 限制最大线程数
    size_t thread_size = tasks.size();
    if (thread_size > max_thread_size_ ) {
        thread_size = max_thread_size_;
    }

    if (ErrCode::ERROR_NONE != initial(thread_size)) {
        cout << "initial threads pool failed. leak of resource." << endl;
    } else {
        cout << "initial threads pool done." << endl;
    }

    // 分任务
    for (auto& task : tasks) {
        cout << "fetch free thread... " << endl;
        while (free_threads_.size() == 0) {
            cout << "fetch free thread... " << endl;
            this_thread::sleep_for (chrono::seconds(1));

        }
        cout << "fetch free thread fininshed." << endl;
        Thread* thread = free_threads_.front();
        free_threads_.pop_front();
        thread->set_task(task);
        thread->activate();
    }

    return ErrCode::ERROR_NONE;
}