##########
# Common #
##########

_LIBMEDIA_HEADERS= \
	libla/la/mat.hpp \
	libla/la/vec.hpp \
	include/media/app.hpp \
	include/media/graphics.hpp \
	include/media/log.hpp \
	include/media/media.hpp \
	include/media/pointer.hpp \
	include/media/sensor.hpp
LIBMEDIA_HEADERS=$(_LIBMEDIA_HEADERS:%=$(LIBMEDIA_DIR)/%)

_LIBMEDIA_INCLUDES=include libla
LIBMEDIA_INCLUDES=$(_LIBMEDIA_INCLUDES:%=$(LIBMEDIA_DIR)/%)

LIBMEDIA_CFLAGS=-std=c++11 -Wall
LIBMEDIA_LFLAGS=

_LIBMEDIA_SOURCE_DIR=source
LIBMEDIA_SOURCE_DIR=$(_LIBMEDIA_SOURCE_DIR:%=$(LIBMEDIA_DIR)/%)

.phony: libmedia_desktop libmedia_web

###########
# Desktop #
###########

_LIBMEDIA_D_SOURCE= \
	desktop/app.cpp \
	desktop/event.cpp \
	desktop/graphics.cpp \
	desktop/main.cpp \
	desktop/pointer.cpp
LIBMEDIA_D_SOURCE=$(_LIBMEDIA_D_SOURCE:%=$(LIBMEDIA_SOURCE_DIR)/%)

LIBMEDIA_D_HEADERS=
LIBMEDIA_D_CFLAGS=
LIBMEDIA_D_LFLAGS=
LIBMEDIA_D_INCLUDES=

_LIBMEDIA_D_LOCAL_HEADERS= \
	desktop/app.hpp \
	desktop/event.hpp \
	desktop/graphics.hpp \
	desktop/pointer.hpp
LIBMEDIA_D_LOCAL_HEADERS=$(_LIBMEDIA_D_LOCAL_HEADERS:%=$(LIBMEDIA_SOURCE_DIR)/%)

LIBMEDIA_D_LOCAL_CFLAGS=
LIBMEDIA_D_LOCAL_INCLUDES=

_LIBMEDIA_D_SOURCE_DIRS=desktop

LIBMEDIA_D_LINK_LIBS=SDL2 GL GLEW

LIBMEDIA_D_OBJ_DIR=$(D_OBJ_DIR)/libmedia
LIBMEDIA_D_OBJ_DIRS=$(LIBMEDIA_D_OBJ_DIR) $(_LIBMEDIA_D_SOURCE_DIRS:%=$(LIBMEDIA_D_OBJ_DIR)/%)

LIBMEDIA_D_LIB_DIR=$(LIBMEDIA_D_OBJ_DIR)
LIBMEDIA_D_LIB=media
LIBMEDIA_D_LIB_FILE=$(LIBMEDIA_D_OBJ_DIR)/$(LIBMEDIA_D_LIB:%=lib%.a)

_LIBMEDIA_D_OBJS= \
	desktop/app.o \
	desktop/event.o \
	desktop/graphics.o \
	desktop/main.o \
	desktop/pointer.o
LIBMEDIA_D_OBJS=$(_LIBMEDIA_D_OBJS:%=$(LIBMEDIA_D_OBJ_DIR)/%)

libmedia_desktop: $(LIBMEDIA_D_OBJ_DIR) $(LIBMEDIA_D_LIB_FILE)

$(LIBMEDIA_D_LIB_FILE): $(LIBMEDIA_D_OBJS)
	ar rcs $@ $^

$(LIBMEDIA_D_OBJ_DIR):
	mkdir -p $(LIBMEDIA_D_OBJ_DIRS)

LIBMEDIA_D_ALL_HEADERS=$(LIBMEDIA_HEADERS) $(LIBMEDIA_D_HEADERS) $(LIBMEDIA_D_LOCAL_HEADERS)
LIBMEDIA_D_ALL_INCLUDES=$(LIBMEDIA_INCLUDES) $(LIBMEDIA_D_INCLUDES) $(LIBMEDIA_D_LOCAL_INCLUDES)
LIBMEDIA_D_ALL_CFLAGS=-c $(LIBMEDIA_CFLAGS) $(LIBMEDIA_D_CFLAGS) $(LIBMEDIA_D_LOCAL_CFLAGS)

$(LIBMEDIA_D_OBJ_DIR)/desktop/app.o: $(LIBMEDIA_SOURCE_DIR)/desktop/app.cpp $(LIBMEDIA_D_ALL_HEADERS)
	$(D_CXX) $(LIBMEDIA_D_ALL_CFLAGS) $(LIBMEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_D_OBJ_DIR)/desktop/event.o: $(LIBMEDIA_SOURCE_DIR)/desktop/event.cpp $(LIBMEDIA_D_ALL_HEADERS)
	$(D_CXX) $(LIBMEDIA_D_ALL_CFLAGS) $(LIBMEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_D_OBJ_DIR)/desktop/graphics.o: $(LIBMEDIA_SOURCE_DIR)/desktop/graphics.cpp $(LIBMEDIA_D_ALL_HEADERS)
	$(D_CXX) $(LIBMEDIA_D_ALL_CFLAGS) $(LIBMEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_D_OBJ_DIR)/desktop/main.o: $(LIBMEDIA_SOURCE_DIR)/desktop/main.cpp $(LIBMEDIA_D_ALL_HEADERS)
	$(D_CXX) $(LIBMEDIA_D_ALL_CFLAGS) $(LIBMEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_D_OBJ_DIR)/desktop/pointer.o: $(LIBMEDIA_SOURCE_DIR)/desktop/pointer.cpp $(LIBMEDIA_D_ALL_HEADERS)
	$(D_CXX) $(LIBMEDIA_D_ALL_CFLAGS) $(LIBMEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

#######
# Web #
#######

_LIBMEDIA_W_SOURCE= \
	web/app.cpp \
	web/main.cpp \
	web/graphics.cpp \
	web/pointer.cpp \
	web/event.cpp \
	web/js/canvas.cpp \
	web/js/handler.cpp \
	web/js/utility.cpp
LIBMEDIA_W_SOURCE=$(_LIBMEDIA_W_SOURCE:%=$(LIBMEDIA_SOURCE_DIR)/%)

LIBMEDIA_W_CFLAGS=
LIBMEDIA_W_LFLAGS= \
	-s EXPORTED_FUNCTIONS="[ \
		'_main', \
		'_libmedia_pointer_move', \
		'_libmedia_pointer_down', \
		'_libmedia_pointer_up', \
		'_libmedia_pointer_click', \
		'_libmedia_pointer_scroll' \
		]" \
	-s NO_EXIT_RUNTIME=1

LIBMEDIA_W_HEADERS=
LIBMEDIA_W_INCLUDES=

_LIBMEDIA_W_PAGE_RES=resources/index.html
LIBMEDIA_W_PAGE_RES=$(_LIBMEDIA_W_PAGE_RES:%=$(LIBMEDIA_DIR)/%)
LIBMEDIA_W_PAGE=$(W_APP_DIR)/index.html

_LIBMEDIA_W_STYLE_RES=resources/style.css
LIBMEDIA_W_STYLE_RES=$(_LIBMEDIA_W_STYLE_RES:%=$(LIBMEDIA_DIR)/%)
LIBMEDIA_W_STYLE=$(W_APP_DIR)/style.css

_LIBMEDIA_W_SCRIPT_RES=resources/media.js
LIBMEDIA_W_SCRIPT_RES=$(_LIBMEDIA_W_SCRIPT_RES:%=$(LIBMEDIA_DIR)/%)
LIBMEDIA_W_SCRIPT=$(W_APP_DIR)/media.js

_LIBMEDIA_W_LOCAL_HEADERS= \
	web/app.hpp \
	web/graphics.hpp \
	web/pointer.hpp \
	web/js/utility.hpp \
	web/js/canvas.hpp \
	web/js/handler.hpp
LIBMEDIA_W_LOCAL_HEADERS=$(_LIBMEDIA_W_LOCAL_HEADERS:%=$(LIBMEDIA_SOURCE_DIR)/%)

LIBMEDIA_W_LOCAL_CFLAGS=
LIBMEDIA_W_LOCAL_INCLUDES=

_LIBMEDIA_W_SOURCE_DIRS=web web/js

LIBMEDIA_W_OBJ_DIR=$(W_OBJ_DIR)/libmedia
LIBMEDIA_W_OBJ_DIRS=$(LIBMEDIA_W_OBJ_DIR) $(_LIBMEDIA_W_SOURCE_DIRS:%=$(LIBMEDIA_W_OBJ_DIR)/%)

LIBMEDIA_W_LIB_DIR=$(LIBMEDIA_W_OBJ_DIR)
LIBMEDIA_W_LIB=media
LIBMEDIA_W_LIB_FILE=$(LIBMEDIA_W_OBJ_DIR)/$(LIBMEDIA_W_LIB:%=lib%.a)

_LIBMEDIA_W_OBJS= \
	web/app.o \
	web/main.o \
	web/graphics.o \
	web/pointer.o \
	web/event.o \
	web/js/canvas.o \
	web/js/handler.o \
	web/js/utility.o
LIBMEDIA_W_OBJS=$(_LIBMEDIA_W_OBJS:%=$(LIBMEDIA_W_OBJ_DIR)/%)

libmedia_web: $(LIBMEDIA_W_OBJ_DIR) $(LIBMEDIA_W_LIB_FILE) $(LIBMEDIA_W_PAGE) $(LIBMEDIA_W_STYLE) $(LIBMEDIA_W_SCRIPT)

$(LIBMEDIA_W_PAGE): $(LIBMEDIA_W_PAGE_RES)
	cp $< $@

$(LIBMEDIA_W_STYLE): $(LIBMEDIA_W_STYLE_RES)
	cp $< $@

$(LIBMEDIA_W_SCRIPT): $(LIBMEDIA_W_SCRIPT_RES)
	cp $< $@

$(LIBMEDIA_W_LIB_FILE): $(LIBMEDIA_W_OBJS)
	ar rcs $@ $^

$(LIBMEDIA_W_OBJ_DIR):
	mkdir -p $(LIBMEDIA_W_OBJ_DIRS)

LIBMEDIA_W_ALL_HEADERS=$(LIBMEDIA_HEADERS) $(LIBMEDIA_W_HEADERS) $(LIBMEDIA_W_LOCAL_HEADERS)
LIBMEDIA_W_ALL_INCLUDES=$(LIBMEDIA_INCLUDES) $(LIBMEDIA_W_INCLUDES) $(LIBMEDIA_W_LOCAL_INCLUDES)
LIBMEDIA_W_ALL_CFLAGS=-c $(LIBMEDIA_CFLAGS) $(LIBMEDIA_W_CFLAGS) $(LIBMEDIA_W_LOCAL_CFLAGS)

$(LIBMEDIA_W_OBJ_DIR)/web/app.o: $(LIBMEDIA_SOURCE_DIR)/web/app.cpp $(LIBMEDIA_W_ALL_HEADERS)
	$(W_CXX) $(LIBMEDIA_W_ALL_CFLAGS) $(LIBMEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_W_OBJ_DIR)/web/main.o: $(LIBMEDIA_SOURCE_DIR)/web/main.cpp $(LIBMEDIA_W_ALL_HEADERS)
	$(W_CXX) $(LIBMEDIA_W_ALL_CFLAGS) $(LIBMEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_W_OBJ_DIR)/web/graphics.o: $(LIBMEDIA_SOURCE_DIR)/web/graphics.cpp $(LIBMEDIA_W_ALL_HEADERS)
	$(W_CXX) $(LIBMEDIA_W_ALL_CFLAGS) $(LIBMEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_W_OBJ_DIR)/web/pointer.o: $(LIBMEDIA_SOURCE_DIR)/web/pointer.cpp $(LIBMEDIA_W_ALL_HEADERS)
	$(W_CXX) $(LIBMEDIA_W_ALL_CFLAGS) $(LIBMEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_W_OBJ_DIR)/web/event.o: $(LIBMEDIA_SOURCE_DIR)/web/event.cpp $(LIBMEDIA_W_ALL_HEADERS)
	$(W_CXX) $(LIBMEDIA_W_ALL_CFLAGS) $(LIBMEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_W_OBJ_DIR)/web/js/canvas.o: $(LIBMEDIA_SOURCE_DIR)/web/js/canvas.cpp $(LIBMEDIA_W_ALL_HEADERS)
	$(W_CXX) $(LIBMEDIA_W_ALL_CFLAGS) $(LIBMEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_W_OBJ_DIR)/web/js/handler.o: $(LIBMEDIA_SOURCE_DIR)/web/js/handler.cpp $(LIBMEDIA_W_ALL_HEADERS)
	$(W_CXX) $(LIBMEDIA_W_ALL_CFLAGS) $(LIBMEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(LIBMEDIA_W_OBJ_DIR)/web/js/utility.o: $(LIBMEDIA_SOURCE_DIR)/web/js/utility.cpp $(LIBMEDIA_W_ALL_HEADERS)
	$(W_CXX) $(LIBMEDIA_W_ALL_CFLAGS) $(LIBMEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@
