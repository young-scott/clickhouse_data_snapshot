#include "config/Context.h"

#include <iostream>
using namespace std;
#include "tools/ThreadPool.h"
#include "tools/TaskFactory.h"


int main(int argc, char** argv) {
    cout << "hello" << endl;

    ContextPtr context_ptr = Context::parse(argc, argv);

    vector<TaskPtr> tasks = TaskFactory::create(context_ptr);
    ThreadPool::instance()->set_max_thread_size(context_ptr->max_thread_size());
    ThreadPool::instance()->process(tasks);

    return 0;
}