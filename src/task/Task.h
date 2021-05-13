#pragma once
#include "common/ErrCode.h"
#include "config/Context.h"


class Task {
public:
    virtual ErrCode run() = 0;

public:
    Task(const ContextPtr & context) : context_(context) {}
    virtual ~Task() {};
    
protected:
    const ContextPtr context_;  /// 所有任务共享同一个task， 当context改变一些参数，task可以不用重启。

};
DECLARE_CLASS_POINT_TYPE(Task);
