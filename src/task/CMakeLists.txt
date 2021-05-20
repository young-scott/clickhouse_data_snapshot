aux_source_directory(../../src/task TASK_SRC)
add_library(Task ${TASK_SRC})
target_link_libraries(Task ClickHouse)

