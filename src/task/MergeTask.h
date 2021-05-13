#pragma once
#include "task/Task.h"

class MergeTask : public Task {
public:
    ErrCode run() override;

};
DECLARE_CLASS_POINT_TYPE(MergeTask);
