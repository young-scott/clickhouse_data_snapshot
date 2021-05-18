#pragma once
#include <sstream>
#include <string>
#include <set>
#include "common/ErrCode.h"
#include "config/Context.h"
#include "clickhouse/Partition.h"

class Task {
public:
    virtual ErrCode run() = 0;

public:
    Task(const ContextPtr & context, string db, string table) : context_(context)
            ,db_(db) ,table_(table) {}
    virtual ~Task() {};

protected:
    int get_last_block_id();
    string root_path(string data_dir, string db, string table);
    map<string, PartitionPtr> scan_partitions(const string& parent_dir);
    
protected:
    const ContextPtr context_;  /// 所有任务共享同一个task， 当context改变一些参数，task可以不用重启。
    const string db_;
    const string table_;
};
DECLARE_CLASS_POINT_TYPE(Task);
