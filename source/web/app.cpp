#include "app.hpp"

#include <media/log.hpp>

using namespace media;

WebApp::WebApp() :
	jscanvas("__libmedia_canvas"),
  graphics(&jscanvas),
  pointer(jscanvas.getName())
{
	
}

WebApp::~WebApp() {
	
}

void WebApp::create() {
	if(getHandler() != nullptr) {
		getHandler()->create();
	} else {
		logWarning("App::Handler is null");
	}
	getGraphics()->create();
	getGraphics()->resize();
}

void WebApp::destroy() {
	getGraphics()->destroy();
	if(getHandler() != nullptr) {
		getHandler()->destroy();
	} else {
		logWarning("App::Handler is null");
	}
}

JSCanvas *WebApp::getCanvas() {
	return &jscanvas;
}

WebGraphics *WebApp::getGraphics() {
	return &graphics;
}
WebPointer *WebApp::getPointer() {
	return &pointer;
}
Sensor *WebApp::getSensor() {
	return nullptr;
}

void WebApp::setHandler(Handler *h) {
	handler = h;
	handler->super = this;
}

App::Handler *WebApp::getHandler() {
	return handler;
}
