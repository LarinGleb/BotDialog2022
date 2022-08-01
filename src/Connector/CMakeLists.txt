cmake_minimum_required(VERSION 3.10)

project(DataBase)

set(Boost_USE_MULTITHREADED ON)

add_library(DataBaseLib SHARED DataBase.cpp)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

include_directories(/usr/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

target_include_directories(DataBaseLib 
                           PUBLIC /usr/include
                           PUBLIC /usr/include/cppconn
                           )

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/local/mysql/connector-c++-/)
include_directories(/usr/include /usr/include/cppconn)
link_directories(/usr/lib/x86_64-linux-gnu)

target_link_libraries(DataBaseLib /usr/lib/x86_64-linux-gnu/libmysqlcppconn.so.7 ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

message("--Added connector")
