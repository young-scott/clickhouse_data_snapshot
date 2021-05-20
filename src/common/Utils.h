#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
using namespace std;


namespace utils {
    inline vector<string> split(const string& str, const string& delim) {
        vector<string> substrs;

        if (str.empty()) {
            return substrs;
        }

        int begin_pos = 0;
        int pos = 0;
        while((pos = str.find(delim, begin_pos)) != string::npos) {
            substrs.push_back(str.substr(begin_pos, pos - begin_pos));
            begin_pos = pos + delim.size();
        }
    
        substrs.push_back(str.substr(begin_pos));
        return substrs;
    }

    inline void copy_dir(string src_path, string dst_path) {
        cout << "copy from dir [" << src_path << "] to dir [" << dst_path << "]." << endl;

        if (!filesystem::exists(filesystem::path(dst_path))) {
            cout << "[" << dst_path << "] path is not existed. create it." << endl;
            filesystem::create_directories(dst_path);
        }
        filesystem::copy(src_path, dst_path, filesystem::copy_options::recursive | filesystem::copy_options::update_existing);
    }

    inline void remove_dir(string path) {
        cout << "remove dir [" << path << "]." << endl;
        filesystem::path remove_path(path);
        if (!filesystem::exists(remove_path)) {
            cout << "[" << path << "] path is not existed. no need to remove it." << endl;
            return;
        }
        filesystem::remove(remove_path);
    }

    inline string concat_path(string directory, string file_name) {
        if (directory[directory.size() -1 ] == '/') {
            return directory + file_name;
        }
        return directory + '/' + file_name;
    }
}

