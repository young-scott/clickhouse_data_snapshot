#pragma once
#include "task/Task.h"

class BackupTask : public Task {
public:
    BackupTask(const ContextPtr& context, const string& db, const string& table);
    virtual ~BackupTask();
public:
    ErrCode run() override;

private:
    const string db_;
    const string table_;
};
DECLARE_CLASS_POINT_TYPE(BackupTask);
