# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(Snake)

add_executable(snake main.cpp)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(snake ${CURSES_LIBRARIES})
