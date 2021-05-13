#include "tools/ThreadPool.h"

shared_ptr<ThreadPool> ThreadPool::instance_;

ErrCode ThreadPool::process(const vector<TaskPtr>& tasks) {
    cout << "receive task size : [" << tasks.size() << "]" << endl;

    /// 限制最大线程数
    thread_size_ = tasks.size();
    if (thread_size_ > max_thread_size_ ) {
        thread_size_ = max_thread_size_;
    }

    if (ErrCode::ERROR_NONE != initial()) {
        cout << "initial threads pool failed. leak of resource." << endl;
    }

    for (size_t i = 0; i < thread_size_; ++i) {
        threads_.push_back(make_shared<Thread>(this));
    }

    // 分任务
    for (auto& task : tasks) {
        cout << "fetch free thread ";
        while (threads_.size() == 0) {
            cout << ".";
            this_thread::sleep_for (chrono::seconds(1));

        }
        cout << "fininshed." << endl;
        ThreadPtr thread = threads_.front();
        threads_.pop_front();
        thread->set_task(task);
        thread->activate();
        ++running;
    }

    return ErrCode::ERROR_NONE;
}