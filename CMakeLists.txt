cmake_minimum_required(VERSION 2.8.4)
project(DialogBot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

set(RAPIDJSON_INCLUDE_DIR /usr/local/include/rapidjson)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR} &{RAPIDJSON_INCLUDE_DIR})

add_executable(Dialog Bot.cpp AdditionalTools.cpp)

add_subdirectory(Connector)
message("Included connector")

add_subdirectory(BotTools)
message("Included bot tools")

add_subdirectory(ReviewBot)
message("Included Review Bot")

add_subdirectory(Error)
message("Included Review Bot utils")

add_subdirectory(Json)
message("Included Review Bot json")

target_link_libraries(Dialog DataBaseLib Tools ReviewBot Event Review Time JSON Error )

target_link_libraries(Dialog /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
add_dependencies(Dialog DataBaseLib Tools ReviewBot Event Review Time JSON Error)