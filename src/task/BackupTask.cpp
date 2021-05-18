#include <iostream>
#include <set>
#include <filesystem>
#include "task/BackupTask.h"
#include "clickhouse/Partition.h"
BackupTask::BackupTask(const ContextPtr& context, const string& db, const string& table) 
    : Task(context, db, table) {

}

BackupTask::~BackupTask() {
    
}

void BackupTask::filter_old_data_parts(int last_block_id, map<string, DataPartPtr>& data_parts) {
    map<string, DataPartPtr> filted_data_parts;
    for (auto& pair : data_parts) {
        if (pair.second->newer(last_block_id)) {
            filted_data_parts.insert(pair);
        }
    }
    data_parts.swap(filted_data_parts);
}


MergeTreeDataPtr load_data_part(const string& data_part_dir) {
    
}


ErrCode BackupTask::validate_data_part(const string& data_part_dir) {

    MergeTreeDataPtr merge_tree_data_ptr = load_data_part(data_part_dir);
    
    return merge_tree_data_ptr->validate();
}

string BackupTask::get_last_partition() {
    return "20210221";
}

ErrCode BackupTask::run() {
    cout << "backup task executed" << endl;
    // int last_block_id = get_last_block_id();
    
    string data_path = root_path(context_->data_path(), db_, table_);
    string replicated_data_path = root_path(context_->replicated_data_path(), db_, table_);

    cout << "data path : [" << data_path << "]." << endl;
    cout << "replicated data path : [" << replicated_data_path << "]." << endl;

    string last_partition = get_last_partition(); 
    int last_block_id;
    while(true) {
        map<string, PartitionPtr> partitions = scan_partitions(data_path);

        // filter_old_data_parts(last_block_id, data_parts);

        for (auto x : partitions) {
            if (last_partition > x.first) {
                continue;
            } else if (last_partition < x.first) {
                last_block_id = 0;
            }
            last_partition = x.first;
            PartitionPtr& partition_ptr = x.second;
            for (auto& data_part : partition_ptr->data_parts) {
                if (data_part->max_block <= last_block_id) {
                    continue;
                }
                string src_dir = utils::concat_path(data_path, data_part->data_part_name);
                string dst_dir = utils::concat_path(replicated_data_path, data_part->data_part_name);
                utils::copy_dir(src_dir, dst_dir);
                if (ErrCode::ERROR_NONE == validate_data_part(dst_dir)) {
                    last_block_id = data_part->max_block;
                } else {
                    utils::remove_dir(dst_dir);
                }
            }
        }
        break;
    }

    cout << "backup task executed finished" << endl;
    return ErrCode::ERROR_NONE;
}