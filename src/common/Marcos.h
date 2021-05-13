// Note(yangchao. 2021-05-13):公共头文件， 不允许在h中添加自己编写的头文件
#pragma once

#include <memory>
using namespace std;

#define DECLARE_CLASS_POINT_TYPE(T) typedef shared_ptr<T> T##Ptr