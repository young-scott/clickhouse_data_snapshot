cmake_minimum_required(VERSION 3.19)

set(CMAKE_BUILD_TYPE debug)

set(PROJECT_SOURCE_DIR " ./")
set(PROJECT_NAME "data_snapshot")



project(${PROJECT_NAME}
        VERSION 0.0.1
        DESCRIPTION "CLICKHOUSE DATA SNPAHSOT"
        LANGUAGES CXX
)

# set language std
set(CMAKE_CXX_STANDARD 17)
# set language std and Disable fallback to a previous version
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable CXX Syntax EXTENSIONS
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(src)
add_subdirectory (cmake/config)
add_subdirectory (cmake/task)
add_subdirectory (cmake/tools)
add_executable (${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} Config Tools Task pthread)


