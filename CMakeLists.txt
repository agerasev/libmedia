cmake_minimum_required(VERSION 2.6)
project(media-test)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g")

set(SOURCE
	source/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})

add_subdirectory(libmedia)
include_directories(libmedia/include)
include_directories(libmedia/libla)

target_link_libraries(${PROJECT_NAME} media)
