#pragma once

#include "graphics.hpp"
#include "pointer.hpp"
#include "sensor.hpp"

#include <string>
#include <vector>

namespace media {
class App {
public:
	class Handler {
	public:
		App *super = nullptr;
		
		virtual void create() {}
		virtual void create(const std::vector<std::string> &) {
			create();
		}
		virtual void destroy() {}
		
		virtual void show() {}
		virtual void hide() {}
		virtual void saveState() {}
	};
	
public:
	App() {}
	virtual ~App() {}
	
	virtual Graphics *getGraphics() = 0;
	virtual Pointer *getPointer() = 0;
	virtual Sensor *getSensor() = 0;
	
	virtual void setHandler(Handler *h) = 0;
	virtual Handler *getHandler() = 0;
};
}

#define MEDIA_SET_APP_HANDLER(app_handler) \
media::App::Handler *__app_handler = (app_handler)
