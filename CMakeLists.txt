cmake_minimum_required(VERSION 2.6)
project(media)

include_directories(include)

set(SOURCE 
	source/common/common.c
	source/desktop/assets.c
	source/desktop/desktop.c
	source/desktop/graphics.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_link_libraries(${PROJECT_NAME} SDL2 GL glew)
