cmake_minimum_required(VERSION 3.10)

add_library(JSON SHARED json.cpp)

# https://cmake.org/cmake/help/latest/command/configure_file.html

`cmake .. ... -D DEFAULT_JSON=true -D USER_NAME ... -D PASSW ... -D`

set(DEFAULT_JSON true)
if (NOT DEFAULT_JSON)
    set(JSON_PATH ${CMAKE_PROJECT_DIR}/defaultSettings.json)
endif()

configure_file(path.h.in)

set_target_properties(JSON PROPERTIES LINKER_LANGUAGE CXX)
message("Added bot json")