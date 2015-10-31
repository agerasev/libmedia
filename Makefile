.phony: all desktop web

D_CC=gcc
D_CXX=g++

W_CC=emcc
W_CXX=em++

SOURCE=source/main.cpp
HEADERS=

D_OBJ_DIR=build/desktop/obj
D_APP_DIR=build/desktop

W_OBJ_DIR=build/web/obj
W_APP_DIR=build/web

LIBMEDIA_DIR=libmedia
include libmedia/Makefile

D_SOURCE=$(SOURCE)

D_HEADERS=$(HEADERS) $(LIBMEDIA_HEADERS) $(LIBMEDIA_D_HEADERS)

D_INCLUDES=$(LIBMEDIA_INCLUDES) $(LIBMEDIA_D_INCLUDES)

D_LIBS=$(LIBMEDIA_D_LIB) $(LIBMEDIA_D_LINK_LIBS)
D_LIB_DIRS=$(LIBMEDIA_D_LIB_DIR)

D_CFLAGS=$(LIBMEDIA_CFLAGS) $(LIBMEDIA_D_CFLAGS) -Wall
D_LFLAGS=$(LIBMEDIA_LFLAGS) $(LIBMEDIA_D_LFLAGS)

W_SOURCE=$(SOURCE)

W_HEADERS=$(HEADERS) $(LIBMEDIA_HEADERS) $(LIBMEDIA_W_HEADERS)

W_INCLUDES=$(LIBMEDIA_INCLUDES) $(LIBMEDIA_W_INCLUDES)

W_LIBS=$(LIBMEDIA_W_LIB) $(LIBMEDIA_W_LINK_LIBS)
W_LIB_DIRS=$(LIBMEDIA_W_LIB_DIR)

W_CFLAGS=$(LIBMEDIA_CFLAGS) $(LIBMEDIA_W_CFLAGS) -Wall
W_LFLAGS=$(LIBMEDIA_LFLAGS) $(LIBMEDIA_W_LFLAGS)

all: build desktop web

desktop: build/desktop libmedia_desktop build/desktop/app

web: build/web libmedia_web build/web/app.js

build:
	mkdir -p build

build/desktop:
	mkdir -p build/desktop

build/desktop/app: $(D_SOURCE) $(D_HEADERS) $(LIBMEDIA_D_LIB_FILE)
	$(D_CXX) $(D_CFLAGS) $(D_LFLAGS) $(D_INCLUDES:%=-I%) $(D_LIB_DIRS:%=-L%) $(D_LIBS:%=-l%) $< -o $@

build/web:
	mkdir -p build/web

build/web/app.js: $(W_SOURCE) $(W_HEADERS) $(LIBMEDIA_W_LIB_FILE)
	$(W_CXX) $(W_CFLAGS) $(W_LFLAGS) $(W_INCLUDES:%=-I%) $(W_LIB_DIRS:%=-L%) $(W_LIBS:%=-l%) $< -o $@
