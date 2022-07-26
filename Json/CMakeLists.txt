cmake_minimum_required(VERSION 3.10)

add_library(JSON SHARED json.cpp)

set_target_properties(JSON PROPERTIES LINKER_LANGUAGE CXX)
message("Added bot json")