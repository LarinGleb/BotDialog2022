cmake_minimum_required(VERSION 3.10)

add_library(Time SHARED Time.cpp)

set_target_properties(Tools PROPERTIES LINKER_LANGUAGE CXX)
message("Added bot reviews")