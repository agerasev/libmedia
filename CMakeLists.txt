cmake_minimum_required(VERSION 2.6)
project(media)

set(TARGET "DESKTOP" CACHE STRING "Target platform. Available: DESKTOP, WEB. Default: DESKTOP.")

if(${TARGET} EQUAL "WEB")
	set(CMAKE_C_COMPILER emcc)
	set(CMAKE_CXX_COMPILER em++)
endif()
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories(include)
include_directories(libla)

if(${TARGET} EQUAL "DESKTOP")
	set(SOURCE 
		source/desktop/main.cpp
		source/desktop/event.cpp
		source/desktop/app.cpp
		source/desktop/graphics.cpp
		source/desktop/pointer.cpp
	)
elseif(${TARGET} EQUAL "WEB")
	set(SOURCE 
		source/web/main.cpp
		source/web/event.cpp
		source/web/app.cpp
		source/web/graphics.cpp
		source/web/pointer.cpp
	)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} 
		-s EXPORTED_FUNCTIONS="[
			'_main',
			'__libmedia_pointer_motion',
			'__libmedia_pointer_down',
			'__libmedia_pointer_up',
			'__libmedia_pointer_click',
			'__libmedia_pointer_scroll'
			]"
		)
endif()

add_library(${PROJECT_NAME} STATIC ${SOURCE})

if(${TARGET} EQUAL "DESKTOP")
	# find_package(GLEW REQUIRED)
	# find_package(SDL2 REQUIRED)
	target_link_libraries(${PROJECT_NAME} SDL2 GL GLEW)
elseif(${TARGET} EQUAL "WEB")
endif()
