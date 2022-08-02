cmake_minimum_required(VERSION 3.10)

add_subdirectory(Event)
add_subdirectory(Review)
add_library(ReviewBot SHARED ReviewBot.cpp)

include_directories(${CMAKE_SOURCE_DIR}/utils Event Review ${CMAKE_SOURCE_DIR}/Time ${CMAKE_SOURCE_DIR}/utils/TelegramTools)

target_link_libraries(ReviewBot Event Review Time)

message("--Added review bot")
