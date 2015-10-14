#include "pointer.hpp"

#include <SDL2/SDL.h>

using namespace media;

void DesktopPointer::setHandler(Handler *h) {
	handler = h;
	if(handler != nullptr) {
		handler->super = this;
	}
}

Pointer::Handler *DesktopPointer::getHandler() {
	return handler;
}

ivec2 DesktopPointer::getPosition(int) const {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return ivec2(x, y);
}

int DesktopPointer::getButtons() const {
	return buttons;
}

void DesktopPointer::move(ivec2 from, ivec2 to) {
	if(handler != nullptr) {
		handler->move(buttons, from, to);
	}
}

void DesktopPointer::up(int button, ivec2 pos, int index) {
	buttons &= ~button;
	if(handler != nullptr) {
		handler->up(buttons, pos, index);
	}
}

void DesktopPointer::down(int button, ivec2 pos, int index) {
	buttons |= button;
	if(handler != nullptr) {
		handler->down(buttons, pos, index);
	}
}

void DesktopPointer::click(int button, ivec2 pos, int index) {
	if(handler != nullptr) {
		handler->click(buttons, pos, index);
	}
}

void DesktopPointer::scroll(ivec2 pos, ivec2 val) {
	if(handler != nullptr) {
		handler->scroll(pos, val);
	}
}
