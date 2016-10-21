cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project (SunsetGlow)
MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -std=c++11")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")

include_directories(include deps/Renacence/include third third/libhdfs/)
file(GLOB SRC_LIBS "src/compute/*.cpp" "src/compute/*.c" "third/protobuf-c/protobuf-c.c" "third/thread/*.cpp" "third/protobuf-c-rpc/*.c")

add_library(SunsetGlow SHARED ${SRC_LIBS})

find_package (Threads)
target_link_libraries(SunsetGlow ${CMAKE_THREAD_LIBS_INIT} Renascence)


add_executable(compute-responser.out ./compute-responser.cpp)
add_executable(compute-server.out ./compute-server.cpp)

target_link_libraries(compute-responser.out SunsetGlow)
target_link_libraries(compute-server.out SunsetGlow)

find_library(HDFSLIBS hdfs)

file(GLOB HDFS_STREAM_CPP src/fs/*.cpp)
find_package(JNI REQUIRED)
add_library(hdfsStream SHARED ${HDFS_STREAM_CPP})

target_link_libraries(hdfsStream ${JAVA_JVM_LIBRARY})
target_link_libraries(hdfsStream hdfs)
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(
        hdfsStream
        )
endif()

add_executable(hdfs_tools.out hdfs_tools.cpp)
target_link_libraries(hdfs_tools.out hdfsStream Renascence)

add_executable(example.out ./example.cpp)
target_link_libraries(example.out Renascence)

target_link_libraries(compute-responser.out hdfsStream)
target_link_libraries(compute-server.out hdfsStream)
