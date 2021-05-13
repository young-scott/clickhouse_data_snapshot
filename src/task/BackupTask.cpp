#include <iostream>
#include "task/BackupTask.h"

BackupTask::BackupTask(const ContextPtr& context, const string& db, const string& table) 
    : Task(context), db_(db), table_(table) {

}

BackupTask::~BackupTask() {
    
}

ErrCode BackupTask::run() {
    cout << "backup task executed" << endl;
    return ErrCode::ERROR_NONE;
}