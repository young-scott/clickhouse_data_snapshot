aux_source_directory(../../src/common COMMON_SRC)
add_library(Common ${COMMON_SRC})
add_dependencies(Common Poco::Foundation)
target_link_libraries(Common Poco::Foundation)

