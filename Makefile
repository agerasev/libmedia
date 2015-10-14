LIBMEDIA_DESKTOP_SOURCES= \
	source/desktop/app.cpp \
	source/desktop/event.cpp \
	source/desktop/graphics.cpp \
	source/desktop/main.cpp \
	source/desktop/pointer.cpp

LIBMEDIA_WEB_SOURCES= \
	source/web/app.cpp \
	source/web/main.cpp \
	source/web/graphics.cpp \
	source/web/pointer.cpp \
	source/web/event.cpp \
	source/web/js/canvas.cpp \
	source/web/js/handler.cpp \
	source/web/js/utility.cpp

LIBMEDIA_HEADERS= \
	libla/la/mat.hpp \
	libla/la/vec.hpp \
	include/media/app.hpp \
	include/media/graphics.hpp \
	include/media/log.hpp \
	include/media/media.hpp \
	include/media/pointer.hpp \
	include/media/sensor.hpp

LIBMEDIA_DESKTOP_HEADERS= \
	source/desktop/app.hpp \
	source/desktop/event.hpp \
	source/desktop/graphics.hpp \
	source/desktop/pointer.hpp

LIBMEDIA_WEB_HEADERS= \
	source/web/app.hpp \
	source/web/graphics.hpp \
	source/web/pointer.hpp \
	source/web/js/utility.hpp \
	source/web/js/canvas.hpp \
	source/web/js/handler.hpp

LIBMEDIA_INCLUDES=include libla

LIBMEDIA_DESKTOP_LIBS=SDL2 GL GLEW

LIBMEDIA_FLAGS=-std=c++11
LIBMEDIA_WEB_FLAGS= \
	-s EXPORTED_FUNCTIONS="[ \
		'_main', \
		'_libmedia_pointer_move', \
		'_libmedia_pointer_down', \
		'_libmedia_pointer_up', \
		'_libmedia_pointer_click', \
		'_libmedia_pointer_scroll' \
		]" \
	-s NO_EXIT_RUNTIME=1

LIBMEDIA_WEB_PAGE=resources/index.html


