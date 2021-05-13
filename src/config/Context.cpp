#include <iostream>
#include "config/Context.h"

ContextPtr Context::parse(int argc, char** argv) {
    ContextPtr context_ptr =  make_shared<Context>();
    cout << "begin parse argcs" << endl;
    context_ptr->data_path_ = "/Users/80300388/workspace/clickhouse_data_snapshot/data/";
    context_ptr->db_and_tables_.emplace_back(make_pair("test_db", "test_table"));


    return context_ptr;
}


Context::Context() {
    max_thread_size_ = 1;
}