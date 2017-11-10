cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/includes)

add_library(jinlib
            SHARED
            src/main/cpp/gles_code.cpp)

target_link_libraries(jinlib
                      android
                      log
                      EGL
                      GLESv2)