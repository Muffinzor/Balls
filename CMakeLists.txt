cmake_minimum_required(VERSION 3.10)
project(Billiard)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML COMPONENTS system window graphics REQUIRED)

set(BOX2D_INCLUDE_DIR "/usr/include/box2d")
set(BOX2D_LIBRARY "/usr/lib/x86_64-linux-gnu/libbox2d.so")

include_directories(${BOX2D_INCLUDE_DIR})

add_executable(Billiard main.cpp)

target_link_libraries(Billiard
        sfml-graphics
        sfml-window
        sfml-system
        ${BOX2D_LIBRARY}
)
