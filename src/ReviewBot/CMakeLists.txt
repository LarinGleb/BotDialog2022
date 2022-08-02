cmake_minimum_required(VERSION 3.10)

add_library(ReviewBot SHARED ReviewBot.cpp)

include_directories(${CMAKE_SOURCE_DIR}/BotTools Event Review Time)
target_link_libraries(ReviewBot Tools Event Review Time)

message("Added review bot")
