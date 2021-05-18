#pragma once
#include "common/Marcos.h"
#include "config/Context.h"

class MetadataManager
{
public:
    shared_ptr<MetadataManager> instance() {
        if (instance_) {
            return instance_;
        }
        instance_ = make_shared<MetadataManager>();
        return instance_;
    }

    void bind_context(ContextPtr& context_ptr) {
        context_ptr_ = context_ptr;
    }

public:
    string get_last_block_id(const string& db, const string& table) {
        string meta_data_path = concat_path(context_ptr_->metadata_path(), db + "/" + "table");
        
    }

private:
    shared_ptr<MetadataManager> instance_;
    ContextPtr context_ptr_;

};
DECLARE_CLASS_POINT_TYPE(MetadataManager);