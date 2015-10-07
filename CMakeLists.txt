cmake_minimum_required(VERSION 2.6)
project(media)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories(include)

set(SOURCE 
	source/desktop.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

# find_package(GLEW REQUIRED)
# find_package(SDL2 REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2 GL GLEW)
