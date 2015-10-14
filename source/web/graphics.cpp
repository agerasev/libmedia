#include <media/log.hpp>

#include "graphics.hpp"

using namespace media;

WebGraphics::WebGraphics(JSCanvas *canvas) : 
  jscanvas(canvas), 
  width(800), height(600)
{
	jscanvas->setBounds(width, height);
}

WebGraphics::~WebGraphics() {
	
}

ivec2 WebGraphics::getBounds() const {
	return ivec2(width, height);
}

void WebGraphics::create() {
	if(getHandler() != nullptr) {
		getHandler()->create();
	}
}

void WebGraphics::destroy() {
	if(getHandler() != nullptr) {
		getHandler()->destroy();
	}
}

void WebGraphics::resize() {
	if(getHandler() != nullptr) {
		ivec2 s = getBounds();
		getHandler()->resize(s.x(), s.y());
	}
}

void WebGraphics::resize(int w, int h) {
	width = w;
	height = h;
	resize();
}

JSCanvas *WebGraphics::getCanvas() {
	return jscanvas;
}

void WebGraphics::setHandler(Handler *h) {
	handler = h;
	if(handler != nullptr) {
		handler->super = this;
	}
}

Graphics::Handler *WebGraphics::getHandler() const {
	return handler;
}
