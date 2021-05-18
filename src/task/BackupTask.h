#pragma once
#include "task/Task.h"

class BackupTask : public Task {
public:
    BackupTask(const ContextPtr& context, const string& db, const string& table);
    virtual ~BackupTask();
public:
    ErrCode run() override;

private:
    ErrCode validate_data_part(string data_part_dir);
    void filter_old_data_parts(int last_block_id, map<string, DataPartPtr>& data_parts);
    string get_last_partition();
};
DECLARE_CLASS_POINT_TYPE(BackupTask);
