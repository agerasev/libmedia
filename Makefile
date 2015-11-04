##########
# Common #
##########

# Requires:
#  MEDIA_DIR
#  LIBLA_DIR

# Provides:
#  MEDIA_HEADERS
#  MEDIA_INCLUDES
#  MEDIA_CFLAGS

_MEDIA_HEADERS= \
	libla/la/mat.hpp \
	libla/la/vec.hpp \
	include/media/app.hpp \
	include/media/graphics.hpp \
	include/media/log.hpp \
	include/media/media.hpp \
	include/media/pointer.hpp \
	include/media/sensor.hpp
MEDIA_HEADERS=$(_MEDIA_HEADERS:%=$(MEDIA_DIR)/%)

_MEDIA_INCLUDES=include
MEDIA_INCLUDES=$(_MEDIA_INCLUDES:%=$(MEDIA_DIR)/%)

MEDIA_CFLAGS=-std=c++11 -Wall
MEDIA_LFLAGS=

_MEDIA_SOURCE_DIR=source
MEDIA_SOURCE_DIR=$(_MEDIA_SOURCE_DIR:%=$(MEDIA_DIR)/%)

.phony: libmedia_desktop libmedia_web

###########
# Desktop #
###########

_MEDIA_D_SOURCE= \
	desktop/app.cpp \
	desktop/event.cpp \
	desktop/graphics.cpp \
	desktop/main.cpp \
	desktop/pointer.cpp
MEDIA_D_SOURCE=$(_MEDIA_D_SOURCE:%=$(MEDIA_SOURCE_DIR)/%)

MEDIA_D_HEADERS=
MEDIA_D_CFLAGS=
MEDIA_D_LFLAGS=
MEDIA_D_INCLUDES=

_MEDIA_D_LOCAL_HEADERS= \
	desktop/app.hpp \
	desktop/event.hpp \
	desktop/graphics.hpp \
	desktop/pointer.hpp
MEDIA_D_LOCAL_HEADERS=$(_MEDIA_D_LOCAL_HEADERS:%=$(MEDIA_SOURCE_DIR)/%)

MEDIA_D_LOCAL_CFLAGS=
MEDIA_D_LOCAL_INCLUDES=$(LIBLA_DIR)

_MEDIA_D_SOURCE_DIRS=desktop

MEDIA_D_LINK_LIBS=SDL2 GL GLEW

MEDIA_D_OBJ_DIR=$(D_OBJ_DIR)/libmedia
MEDIA_D_OBJ_DIRS=$(MEDIA_D_OBJ_DIR) $(_MEDIA_D_SOURCE_DIRS:%=$(MEDIA_D_OBJ_DIR)/%)

MEDIA_D_LIB_DIR=$(MEDIA_D_OBJ_DIR)
MEDIA_D_LIB=media
MEDIA_D_LIB_FILE=$(MEDIA_D_LIB_DIR)/$(MEDIA_D_LIB:%=lib%.a)

_MEDIA_D_OBJS= \
	desktop/app.o \
	desktop/event.o \
	desktop/graphics.o \
	desktop/main.o \
	desktop/pointer.o
MEDIA_D_OBJS=$(_MEDIA_D_OBJS:%=$(MEDIA_D_OBJ_DIR)/%)

libmedia_desktop: $(MEDIA_D_OBJ_DIR) $(MEDIA_D_LIB_FILE)

$(MEDIA_D_LIB_FILE): $(MEDIA_D_OBJS)
	$(AR) rcs $@ $^

$(MEDIA_D_OBJ_DIR):
	mkdir -p $(MEDIA_D_OBJ_DIRS)

MEDIA_D_ALL_HEADERS=$(MEDIA_HEADERS) $(MEDIA_D_HEADERS) $(MEDIA_D_LOCAL_HEADERS)
MEDIA_D_ALL_INCLUDES=$(MEDIA_INCLUDES) $(MEDIA_D_INCLUDES) $(MEDIA_D_LOCAL_INCLUDES)
MEDIA_D_ALL_CFLAGS=-c $(MEDIA_CFLAGS) $(MEDIA_D_CFLAGS) $(MEDIA_D_LOCAL_CFLAGS)

$(MEDIA_D_OBJ_DIR)/desktop/app.o: $(MEDIA_SOURCE_DIR)/desktop/app.cpp $(MEDIA_D_ALL_HEADERS)
	$(D_CXX) $(MEDIA_D_ALL_CFLAGS) $(MEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_D_OBJ_DIR)/desktop/event.o: $(MEDIA_SOURCE_DIR)/desktop/event.cpp $(MEDIA_D_ALL_HEADERS)
	$(D_CXX) $(MEDIA_D_ALL_CFLAGS) $(MEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_D_OBJ_DIR)/desktop/graphics.o: $(MEDIA_SOURCE_DIR)/desktop/graphics.cpp $(MEDIA_D_ALL_HEADERS)
	$(D_CXX) $(MEDIA_D_ALL_CFLAGS) $(MEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_D_OBJ_DIR)/desktop/main.o: $(MEDIA_SOURCE_DIR)/desktop/main.cpp $(MEDIA_D_ALL_HEADERS)
	$(D_CXX) $(MEDIA_D_ALL_CFLAGS) $(MEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_D_OBJ_DIR)/desktop/pointer.o: $(MEDIA_SOURCE_DIR)/desktop/pointer.cpp $(MEDIA_D_ALL_HEADERS)
	$(D_CXX) $(MEDIA_D_ALL_CFLAGS) $(MEDIA_D_ALL_INCLUDES:%=-I%) $< -o $@

#######
# Web #
#######

# Provides:
#  MEDIA_W_EXPORTED_FUNCTIONS

_MEDIA_W_SOURCE= \
	web/app.cpp \
	web/main.cpp \
	web/graphics.cpp \
	web/pointer.cpp \
	web/event.cpp \
	web/js/canvas.cpp \
	web/js/handler.cpp \
	web/js/utility.cpp
MEDIA_W_SOURCE=$(_MEDIA_W_SOURCE:%=$(MEDIA_SOURCE_DIR)/%)

MEDIA_W_CFLAGS=
MEDIA_W_LFLAGS= \
	-s NO_EXIT_RUNTIME=1

MEDIA_W_EXPORTED_FUNCTIONS=\
	_main \
	_libmedia_pointer_move \
	_libmedia_pointer_down \
	_libmedia_pointer_up \
	_libmedia_pointer_scroll \
	_libmedia_redraw_frame

MEDIA_W_HEADERS=
MEDIA_W_INCLUDES=

_MEDIA_W_PAGE_RES=resources/index.html
MEDIA_W_PAGE_RES=$(_MEDIA_W_PAGE_RES:%=$(MEDIA_DIR)/%)
MEDIA_W_PAGE=$(W_APP_DIR)/index.html

_MEDIA_W_STYLE_RES=resources/style.css
MEDIA_W_STYLE_RES=$(_MEDIA_W_STYLE_RES:%=$(MEDIA_DIR)/%)
MEDIA_W_STYLE=$(W_APP_DIR)/style.css

_MEDIA_W_SCRIPT_RES=resources/media.js
MEDIA_W_SCRIPT_RES=$(_MEDIA_W_SCRIPT_RES:%=$(MEDIA_DIR)/%)
MEDIA_W_SCRIPT=$(W_APP_DIR)/media.js

_MEDIA_W_LOCAL_HEADERS= \
	web/app.hpp \
	web/graphics.hpp \
	web/pointer.hpp \
	web/js/utility.hpp \
	web/js/canvas.hpp \
	web/js/handler.hpp
MEDIA_W_LOCAL_HEADERS=$(_MEDIA_W_LOCAL_HEADERS:%=$(MEDIA_SOURCE_DIR)/%)

MEDIA_W_LOCAL_CFLAGS=
MEDIA_W_LOCAL_INCLUDES=$(LIBLA_DIR)

_MEDIA_W_SOURCE_DIRS=web web/js

MEDIA_W_OBJ_DIR=$(W_OBJ_DIR)/libmedia
MEDIA_W_OBJ_DIRS=$(MEDIA_W_OBJ_DIR) $(_MEDIA_W_SOURCE_DIRS:%=$(MEDIA_W_OBJ_DIR)/%)

MEDIA_W_LIB_DIR=$(MEDIA_W_OBJ_DIR)
MEDIA_W_LIB=media
MEDIA_W_LIB_FILE=$(MEDIA_W_OBJ_DIR)/$(MEDIA_W_LIB:%=lib%.a)

_MEDIA_W_OBJS= \
	web/app.o \
	web/main.o \
	web/graphics.o \
	web/pointer.o \
	web/event.o \
	web/js/canvas.o \
	web/js/handler.o \
	web/js/utility.o
MEDIA_W_OBJS=$(_MEDIA_W_OBJS:%=$(MEDIA_W_OBJ_DIR)/%)

libmedia_web: $(MEDIA_W_OBJ_DIR) $(MEDIA_W_LIB_FILE) $(MEDIA_W_PAGE) $(MEDIA_W_STYLE) $(MEDIA_W_SCRIPT)

$(MEDIA_W_PAGE): $(MEDIA_W_PAGE_RES)
	cp $< $@

$(MEDIA_W_STYLE): $(MEDIA_W_STYLE_RES)
	cp $< $@

$(MEDIA_W_SCRIPT): $(MEDIA_W_SCRIPT_RES)
	cp $< $@

$(MEDIA_W_LIB_FILE): $(MEDIA_W_OBJS)
	$(AR) rcs $@ $^

$(MEDIA_W_OBJ_DIR):
	mkdir -p $(MEDIA_W_OBJ_DIRS)

MEDIA_W_ALL_HEADERS=$(MEDIA_HEADERS) $(MEDIA_W_HEADERS) $(MEDIA_W_LOCAL_HEADERS)
MEDIA_W_ALL_INCLUDES=$(MEDIA_INCLUDES) $(MEDIA_W_INCLUDES) $(MEDIA_W_LOCAL_INCLUDES)
MEDIA_W_ALL_CFLAGS=-c $(MEDIA_CFLAGS) $(MEDIA_W_CFLAGS) $(MEDIA_W_LOCAL_CFLAGS)

$(MEDIA_W_OBJ_DIR)/web/app.o: $(MEDIA_SOURCE_DIR)/web/app.cpp $(MEDIA_W_ALL_HEADERS)
	$(W_CXX) $(MEDIA_W_ALL_CFLAGS) $(MEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_W_OBJ_DIR)/web/main.o: $(MEDIA_SOURCE_DIR)/web/main.cpp $(MEDIA_W_ALL_HEADERS)
	$(W_CXX) $(MEDIA_W_ALL_CFLAGS) $(MEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_W_OBJ_DIR)/web/graphics.o: $(MEDIA_SOURCE_DIR)/web/graphics.cpp $(MEDIA_W_ALL_HEADERS)
	$(W_CXX) $(MEDIA_W_ALL_CFLAGS) $(MEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_W_OBJ_DIR)/web/pointer.o: $(MEDIA_SOURCE_DIR)/web/pointer.cpp $(MEDIA_W_ALL_HEADERS)
	$(W_CXX) $(MEDIA_W_ALL_CFLAGS) $(MEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_W_OBJ_DIR)/web/event.o: $(MEDIA_SOURCE_DIR)/web/event.cpp $(MEDIA_W_ALL_HEADERS)
	$(W_CXX) $(MEDIA_W_ALL_CFLAGS) $(MEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_W_OBJ_DIR)/web/js/canvas.o: $(MEDIA_SOURCE_DIR)/web/js/canvas.cpp $(MEDIA_W_ALL_HEADERS)
	$(W_CXX) $(MEDIA_W_ALL_CFLAGS) $(MEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_W_OBJ_DIR)/web/js/handler.o: $(MEDIA_SOURCE_DIR)/web/js/handler.cpp $(MEDIA_W_ALL_HEADERS)
	$(W_CXX) $(MEDIA_W_ALL_CFLAGS) $(MEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@

$(MEDIA_W_OBJ_DIR)/web/js/utility.o: $(MEDIA_SOURCE_DIR)/web/js/utility.cpp $(MEDIA_W_ALL_HEADERS)
	$(W_CXX) $(MEDIA_W_ALL_CFLAGS) $(MEDIA_W_ALL_INCLUDES:%=-I%) $< -o $@
