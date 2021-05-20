#pragma once

#include "common/Marcos.h"
#include "common/ErrCode.h"
class MergeTreeData {
public:
    static ErrCode checkDataPart(const string & full_relative_path);
    ErrCode validate() { 
        return ErrCode::ERROR_NONE;
    }
};
DECLARE_CLASS_POINT_TYPE(MergeTreeData);