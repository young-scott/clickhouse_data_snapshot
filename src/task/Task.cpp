#include <string>
#include <iostream>
#include "task/Task.h"
#include "common/Utils.h"
using namespace std;

string Task::root_path(string data_dir, string db, string table) {
    return utils::concat_path(data_dir, db + "/" + table);
}

int Task::get_last_block_id() {
    return 0;
}

map<string, PartitionPtr> Task::scan_partitions(const string& parent_dir) {
    map<string, PartitionPtr> partitions;
	filesystem::directory_entry entry(parent_dir);
	if (entry.status().type() != filesystem::file_type::directory) {
        cout << "path [" << parent_dir << "] is not directory" << endl;
        return partitions;
    }

    filesystem::directory_iterator sub_dirs(parent_dir);
    for (auto& it : sub_dirs) {
        const string& data_part_dir = it.path().filename();
        cout << data_part_dir<< endl;	
        DataPartPtr data_part = DataPart::parse(data_part_dir);
        if (!data_part) {
            cout << "filter data part dir [" << data_part_dir << "]" << endl;
            continue;
        } 

        if (!partitions[data_part->partition_id]) {
            partitions[data_part->partition_id].reset(new Partition());
        }
        partitions[data_part->partition_id]->add_data_part(data_part);
    }

    for (auto & pair : partitions) {
        cout << "\"" << pair.first << "\" find parttiton {" << pair.second->debug() << "}." << endl;
    }
    return partitions;
}