#pragma once

#include "common/Marcos.h"

class MergeTreeDataPart {
    static bool checkDataPart(const string & full_relative_path);
};
DECLARE_CLASS_POINT_TYPE(MergeTreeDataPart);