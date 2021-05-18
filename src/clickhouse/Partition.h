#pragma once

#include <sstream>
#include <set>
#include "common/Marcos.h"
#include "clickhouse/DataPart.h"

class Partition {
public:
    string debug() {
        if (data_parts.size() < 1) {
            return "[empty]";
        }
        stringstream ss;
        auto it = data_parts.begin();
        ss << "[" << (*it)->debug();
        for (; it != data_parts.end(); ++it) {
            ss << ", " << (*it)->debug();
        }
        ss << "]";
        return ss.str();
    }

    void add_data_part(DataPartPtr& data_part) {
        data_parts.insert(data_part);
    }

public:
    string partition_id;
    set<DataPartPtr> data_parts;
};
DECLARE_CLASS_POINT_TYPE(Partition);
