cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(Boost_USE_MULTITHREADED ON)
set(RAPIDJSON_INCLUDE_DIR /usr/local/include/rapidjson)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

option(NeedTest "NEED_TEST_BOT" OFF)
if(NeedTest)
    set(TestBot ON)

endif()
configure_file(Bot.h.in Bot.h @ONLY)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/utils ${Boost_INCLUDE_DIR} &{RAPIDJSON_INCLUDE_DIR})

add_executable(dialog-review-bot Bot.cpp)

add_subdirectory(Connector)
message("---Included connector")

add_subdirectory(ReviewBot)
message("---Included Review Bot")

add_subdirectory(Time)
message("---Included Review Bot")

add_subdirectory(Json)
message("---Included Review Bot json")

target_link_libraries(dialog-review-bot DataBaseLib ReviewBot Event Review Time JSON TelegramTools)
target_link_libraries(dialog-review-bot /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

add_dependencies(dialog-review-bot DataBaseLib ReviewBot Event Review Time JSON TelegramTools)
