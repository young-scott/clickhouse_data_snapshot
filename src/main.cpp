#include "config/Context.h"

#include <iostream>
using namespace std;
#include "tools/ThreadPool.h"
#include "tools/TaskFactory.h"
#include "common/Loggers.h"


int main(int argc, char** argv) {
    cout << "hello" << endl;

    ContextPtr context_ptr = Context::parse(argc, argv);
    Logger logger;
    logger.buildLoggers(context_ptr, logger);
    vector<TaskPtr> tasks = TaskFactory::create(context_ptr);
    ThreadPoolPtr instance = make_shared<ThreadPool>(context_ptr->max_thread_size());
    instance->process(tasks);
    cout << "sleep for 5s" << endl;
    std::this_thread::sleep_for(5s);

    instance.reset();
    return 0;
}