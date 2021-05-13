///*
///*  公共头文件， 不允许在h中添加自己编写的头文件
///*
///*  



#pragma once

#include <string>
#include <map>
#include <vector>
#include "common/Marcos.h"


class Context {
public:
    static shared_ptr<Context> parse(int argc, char** argv);
    Context();
    ~Context() = default;

public:
    const string& data_path() {
        return data_path_;
    }

    const vector<pair<string, string>>& db_and_tables() {
        return db_and_tables_;
    }

    size_t max_thread_size() {
        return max_thread_size_;
    }

public:

private:
    string data_path_;
    vector<pair<string, string>> db_and_tables_;

    size_t max_thread_size_;

};
DECLARE_CLASS_POINT_TYPE(Context);
