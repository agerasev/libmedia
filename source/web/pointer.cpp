#include "pointer.hpp"

using namespace media;

WebPointer::WebPointer(const std::string &handler_name) :
	jshandler(handler_name)
{
	
}

void WebPointer::setHandler(Handler *h) {
	handler = h;
	if(handler != nullptr) {
		handler->super = this;
	}
}

Pointer::Handler *WebPointer::getHandler() {
	return handler;
}

ivec2 WebPointer::getPosition(int) const {
	return ivec2(0, 0);
}

int WebPointer::getButtons() const {
	return buttons;
}

void WebPointer::move(ivec2 from, ivec2 to) {
	if(handler != nullptr) {
		handler->move(buttons, from, to);
	}
}

void WebPointer::move(ivec2 to) {
	move(position, to);
	position = to;
}

void WebPointer::up(int button, ivec2 pos, int index) {
	buttons &= ~button;
	if(handler != nullptr) {
		handler->up(buttons, pos, index);
	}
}

void WebPointer::down(int button, ivec2 pos, int index) {
	buttons |= button;
	if(handler != nullptr) {
		handler->down(buttons, pos, index);
	}
}

void WebPointer::click(int button, ivec2 pos, int index) {
	if(handler != nullptr) {
		handler->click(buttons, pos, index);
	}
}

void WebPointer::scroll(ivec2 pos, ivec2 val) {
	if(handler != nullptr) {
		handler->scroll(pos, val);
	}
}
