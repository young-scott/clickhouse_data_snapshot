#include <iostream>
#include "task/BackupTask.h"
#include "tools/TaskFactory.h"

using namespace std;

vector<TaskPtr> TaskFactory::create(const ContextPtr& context) {
    vector<TaskPtr> tasks;

    const string& data_path = context->data_path();
    const vector<pair<string, string>>& db_and_tables = context->db_and_tables();

    for (auto db_and_table : db_and_tables) {
        const string& db = db_and_table.first;
        const string& table = db_and_table.second;
        
        if (ErrCode::ERROR_NONE != validate_path(data_path, db, table)) {
            cout << "data path [" << data_path << "], db [" << db << "] table, [" << table
                    << "] validate path failed" << endl;
        }

        TaskPtr task =  make_shared<BackupTask>(context, db, table);
        cout << "create backup task for " << db << "." << table << endl;
        tasks.push_back(task);
    }

    return move(tasks);
}

ErrCode TaskFactory::validate_path(const string& data_path, const string& db, const string& table) {
    return ErrCode::ERROR_NONE;
}