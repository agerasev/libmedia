#include "app.hpp"

using namespace media;

DesktopApp::DesktopApp() {
	
}

DesktopApp::~DesktopApp() {
	
}

DesktopGraphics *DesktopApp::getGraphics() {
	return &graphics;
}
Pointer *DesktopApp::getPointer() {
	return nullptr;
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
