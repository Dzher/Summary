cmake_minimum_required(VERSION 3.11)
project(Summary VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 COMPONENTS Core Gui Widgets Charts REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(source)
