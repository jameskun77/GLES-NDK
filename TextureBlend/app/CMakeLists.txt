cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/includes)

add_library(jinlib
            SHARED
            src/main/cpp/NativeBridge.cpp
            src/main/cpp/RenderEngine.cpp)

target_link_libraries(jinlib
                      android
                      log
                      EGL
                      GLESv3
                      jnigraphics)