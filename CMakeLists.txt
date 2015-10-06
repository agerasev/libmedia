cmake_minimum_required(VERSION 2.6)
project(media-test)

include_directories(include)

set(SOURCE
	source/main.c
)

add_executable(${PROJECT_NAME} ${SOURCE})

add_subdirectory(libmedia)
include_directories(libmedia/include)
target_link_libraries(${PROJECT_NAME} media)
