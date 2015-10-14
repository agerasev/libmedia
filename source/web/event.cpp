#include "app.hpp"

#include <media/log.hpp>

using namespace media;

extern WebApp *__app;

extern "C" {
void libmedia_pointer_move(int x, int y, int dx, int dy) {
	if(dx == 0 && dy == 0) {
		__app->getPointer()->move(ivec2(x, y));
	} else {
		__app->getPointer()->move(ivec2(x - dx, y - dy), ivec2(x, y));
	}
}

void libmedia_pointer_down(int x, int y, int bb) {
	int b = 0;
	switch(bb) {
	case 0: b = Pointer::LEFT; break;
	case 1: b = Pointer::MIDDLE; break;
	case 2: b = Pointer::RIGHT; break;
	default: break;
	}
	__app->getPointer()->down(b, ivec2(x, y));
}

void libmedia_pointer_up(int x, int y, int bb) {
	int b = 0;
	switch(bb) {
	case 0: b = Pointer::LEFT; break;
	case 1: b = Pointer::MIDDLE; break;
	case 2: b = Pointer::RIGHT; break;
	default: break;
	}
	__app->getPointer()->up(b, ivec2(x, y));
}

void libmedia_pointer_click(int x, int y, int bb) {
	int b = 0;
	switch(bb) {
	case 0: b = Pointer::LEFT; break;
	case 1: b = Pointer::MIDDLE; break;
	case 2: b = Pointer::RIGHT; break;
	default: break;
	}
	__app->getPointer()->click(b, ivec2(x, y));
}

void libmedia_pointer_scroll() {
	logMessage("pointer scroll");
}
}
