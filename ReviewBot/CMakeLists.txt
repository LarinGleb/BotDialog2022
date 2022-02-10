cmake_minimum_required(VERSION 3.10)

add_library(ReviewBot SHARED ReviewBot.cpp)

include_directories(Tools PUBLIC ${CMAKE_SOURCE_DIR}/BotTools)
message("Added review bot")