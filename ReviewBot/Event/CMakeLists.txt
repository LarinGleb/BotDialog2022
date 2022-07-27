cmake_minimum_required(VERSION 3.10)

add_library(Event SHARED Event.cpp WorkingEvent.cpp AddEvent.cpp)

set_target_properties(Event PROPERTIES LINKER_LANGUAGE CXX)
message("Added bot event")