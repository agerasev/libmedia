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

static int bb_to_b(int bb) {
	return
	    !!(bb & 1)*Pointer::LEFT | 
	    !!(bb & 2)*Pointer::RIGHT | 
	    !!(bb & 4)*Pointer::MIDDLE;
}

void libmedia_pointer_down(int x, int y, int bb) {
	__app->getPointer()->down(bb_to_b(bb), ivec2(x, y));
}

void libmedia_pointer_up(int x, int y, int bb) {
	__app->getPointer()->up(bb_to_b(bb), ivec2(x, y));
}

void libmedia_pointer_click(int x, int y, int bb) {
	__app->getPointer()->click(bb_to_b(bb), ivec2(x, y));
}

void libmedia_pointer_scroll() {
	logMessage("pointer scroll");
}
}
