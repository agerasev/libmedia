#include "app.hpp"

using namespace media;

DesktopApp::DesktopApp() {
	
}

DesktopApp::~DesktopApp() {
	
}

void DesktopApp::create() {
	getHandler()->create();
	getGraphics()->create();
	getGraphics()->resize();
}

void DesktopApp::destroy() {
	getHandler()->destroy();
	getGraphics()->destroy();
}

DesktopGraphics *DesktopApp::getGraphics() {
	return &graphics;
}
DesktopPointer *DesktopApp::getPointer() {
	return &pointer;
}
Sensor *DesktopApp::getSensor() {
	return nullptr;
}

void DesktopApp::setHandler(Handler *h) {
	handler = h;
	handler->super = this;
}

App::Handler *DesktopApp::getHandler() {
	return handler;
}
