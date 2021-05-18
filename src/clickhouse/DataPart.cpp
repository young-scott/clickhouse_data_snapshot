#include <memory>
#include <sstream>
#include "clickhouse/DataPart.h"


shared_ptr<DataPart> DataPart::parse(const string& data_part_name) {
    DataPartPtr data_part_ptr = make_shared<DataPart>();

    vector<string> substrings = utils::split(data_part_name, DATA_PART_DIRNAME_DELIM);
    if (substrings.size() < 4) {
        return nullptr;
    }

    data_part_ptr->data_part_name = data_part_name;
    data_part_ptr->partition_id = substrings[0];
    data_part_ptr->min_block = atoi(substrings[1].data());
    data_part_ptr->max_block = atoi(substrings[2].data());
    data_part_ptr->level = atoi(substrings[3].data());

    return data_part_ptr;
}

string DataPart::debug() {
    stringstream ss;
    ss << "partition id : " << partition_id << ", ";
    ss << "partition id : " << min_block << ", ";
    ss << "partition id : " << max_block;
    return ss.str();
}