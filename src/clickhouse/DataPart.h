#pragma once

#include <string>
#include <vector>

#include "common/Utils.h"
#include "common/Marcos.h"

static const string DATA_PART_DIRNAME_DELIM = "_";

using namespace std;
class DataPart {
public:
    static shared_ptr<DataPart> parse(const string& data_part_name);
    bool newer(int block_id) {
        return max_block > block_id;
    }
    string debug();

public:
    string data_part_name;
    string partition_id;
    int min_block;
    int max_block;
    int level;
};

DECLARE_CLASS_POINT_TYPE(DataPart);
