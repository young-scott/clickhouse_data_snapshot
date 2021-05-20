#pragma once
#include <vector>
#include <string>
#include <map>
#include "task/Task.h"

class TaskFactory {
public:
    static vector<TaskPtr> create(const ContextPtr & context);

private:
    static ErrCode validate_path(const string& data_path, const string& db, const string& table);

};
DECLARE_CLASS_POINT_TYPE(TaskFactory);

