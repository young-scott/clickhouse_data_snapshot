cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE debug)

set(PROJECT_SOURCE_DIR " ./")
set(PROJECT_NAME "data_snapshot")



project(${PROJECT_NAME}
        VERSION 0.0.1
        DESCRIPTION "CLICKHOUSE DATA SNPAHSOT"
        LANGUAGES CXX
)

# set language std
set(CMAKE_CXX_STANDARD 20)
# set language std and Disable fallback to a previous version
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable CXX Syntax EXTENSIONS
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(src)
include_directories(contrib/poco)
include_directories(contrib/fmt/include)
include_directories(contrib/poco/Foundation/include)
include_directories(contrib/poco/Util/include)


add_subdirectory (src/config)
add_subdirectory (src/task)
add_subdirectory (src/tools)
add_subdirectory (src/common)

add_subdirectory (contrib/poco)
add_subdirectory (contrib/fmt)


add_executable (${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} Config Tools Task ClickHouse Common pthread)


