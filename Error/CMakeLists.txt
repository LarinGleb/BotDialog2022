cmake_minimum_required(VERSION 3.10)

add_library(Error SHARED ErrorSave.cpp)

set_target_properties(Error PROPERTIES LINKER_LANGUAGE CXX)
message("Added bot Error")