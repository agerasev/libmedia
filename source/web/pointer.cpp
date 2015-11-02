#include "pointer.hpp"

using namespace media;

ivec2 WebPointer::center(ivec2 pos) const {
	ivec2 d = jscanvas->getBounds()/2;
	return ivec2(pos.x() - d.x(), d.y() - pos.y());
}

WebPointer::WebPointer(JSCanvas *canvas) :
	jscanvas(canvas), jshandler(canvas)
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
		handler->move(buttons, center(from), center(to));
	}
}

void WebPointer::move(ivec2 to) {
	move(position, to);
	position = to;
}

void WebPointer::up(int button, ivec2 pos, int index) {
	buttons &= ~button;
	if(handler != nullptr) {
		handler->up(buttons, center(pos), index);
	}
}

void WebPointer::down(int button, ivec2 pos, int index) {
	buttons |= button;
	if(handler != nullptr) {
		handler->down(buttons, center(pos), index);
	}
}

void WebPointer::scroll(ivec2 pos, ivec2 val) {
	if(handler != nullptr) {
		handler->scroll(center(pos), val);
	}
}
