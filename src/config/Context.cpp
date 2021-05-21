#include <iostream>
#include "config/Context.h"

ContextPtr Context::parse(int argc, char** argv) {
    ContextPtr context_ptr =  make_shared<Context>();
    cout << "begin parse argcs" << endl;
    context_ptr->data_path_ = "/Users/80300388/workspace/clickhouse_data_snapshot/data/";
    context_ptr->replicated_data_path_ = "/Users/80300388/workspace/clickhouse_data_snapshot/copy/";

    context_ptr->db_and_tables_.emplace_back(make_pair("test_db", "cohort_local"));
    context_ptr->logger_level_="debug";

    return context_ptr;
}


Context::Context() {
    max_thread_size_ = 1;
}