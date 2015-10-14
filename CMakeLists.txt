cmake_minimum_required(VERSION 2.6)
project(media-test)

set(TARGET "DESKTOP" CACHE STRING "Target platform. Available: DESKTOP, WEB. Default: DESKTOP.")

if(${TARGET} EQUAL "WEB")
	set(CMAKE_C_COMPILER emcc)
	set(CMAKE_CXX_COMPILER em++)
endif()
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

set(SOURCE
	source/main.cpp
)

add_subdirectory(libmedia)
include_directories(libmedia/include)
include_directories(libmedia/libla)

if(${TARGET} EQUAL "DESKTOP")
	add_executable(${PROJECT_NAME} ${SOURCE})
	target_link_libraries(${PROJECT_NAME} media)
elseif(${TARGET} EQUAL "WEB")
	add_executable(${PROJECT_NAME}.js ${SOURCE})
	target_link_libraries(${PROJECT_NAME}.js media)
endif()
