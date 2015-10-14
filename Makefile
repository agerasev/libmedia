.phony: all desktop web

CXX=g++
EMXX=em++

SOURCES=source/main.cpp
HEADERS=

ALL_DESKTOP_SOURCES=$(SOURCES) $(LIBMEDIA_DESKTOP_SOURCES:%=libmedia/%)
ALL_WEB_SOURCES=$(SOURCES) $(LIBMEDIA_WEB_SOURCES:%=libmedia/%)

ALL_DESKTOP_HEADERS=$(HEADERS) $(LIBMEDIA_HEADERS:%=libmedia/%) $(LIBMEDIA_DESKTOP_HEADERS:%=libmedia/%)
ALL_WEB_HEADERS=$(HEADERS) $(LIBMEDIA_HEADERS:%=libmedia/%) $(LIBMEDIA_WEB_HEADERS:%=libmedia/%)

ALL_INCLUDES=$(LIBMEDIA_INCLUDES:%=libmedia/%)

ALL_DESKTOP_LIBS=$(LIBMEDIA_DESKTOP_LIBS)

ALL_DESKTOP_FLAGS=$(LIBMEDIA_FLAGS) -Wall
ALL_WEB_FLAGS=$(LIBMEDIA_FLAGS) $(LIBMEDIA_WEB_FLAGS) -Wall

include libmedia/Makefile

all: desktop web

desktop: build build/desktop build/desktop/app
	
web: build build/web build/web/app.js build/web/index.html

build:
	mkdir -p build

build/desktop:
	mkdir -p build/desktop

build/web:
	mkdir -p build/web

build/desktop/app: $(ALL_DESKTOP_SOURCES) $(ALL_DESKTOP_HEADERS)
	$(CXX) $(ALL_DESKTOP_FLAGS) $(ALL_DESKTOP_SOURCES) -o $@ $(ALL_INCLUDES:%=-I%) $(ALL_DESKTOP_LIBS:%=-l%)

build/web/app.js: $(ALL_WEB_SOURCES) $(ALL_WEB_HEADERS)
	$(EMXX) $(ALL_WEB_FLAGS) $(ALL_WEB_SOURCES) -o $@ $(ALL_INCLUDES:%=-I%)

build/web/index.html:
	cp $(LIBMEDIA_WEB_PAGE:%=libmedia/%) $@
