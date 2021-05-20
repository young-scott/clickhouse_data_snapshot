#include <iostream>
#include <thread>
#include "tools/ThreadPool.h"
#include "task/TaskFactory.h"
#include "common/Loggers.h"
#include "config/Context.h"

using namespace std;


int main(int argc, char** argv) {
    cout << "hello" << endl;

    ContextPtr context_ptr = Context::parse(argc, argv);
    Loggers::buildLoggers(context_ptr,  Poco::Logger::root());
    vector<TaskPtr> tasks = TaskFactory::create(context_ptr);
    ThreadPoolPtr instance = make_shared<ThreadPool>(context_ptr->max_thread_size());
    instance->process(tasks);
    cout << "sleep for 5s" << endl;
    std::this_thread::sleep_for(5s);

    instance.reset();
    return 0;
}