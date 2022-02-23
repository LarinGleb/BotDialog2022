cmake_minimum_required(VERSION 3.10)

add_library(ReviewBot SHARED ReviewBot.cpp)

include_directories(Tools ${CMAKE_SOURCE_DIR}/BotTools)
target_link_libraries(ReviewBot Tools)

message("Added review bot")
