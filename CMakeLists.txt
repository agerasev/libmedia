cmake_minimum_required(VERSION 2.6)
project(media)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g")

include_directories(include)
include_directories(libla)

set(SOURCE 
	source/main.cpp
	source/event.cpp
	source/app.cpp
	source/graphics.cpp
	source/pointer.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

# find_package(GLEW REQUIRED)
# find_package(SDL2 REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2 GL GLEW)
