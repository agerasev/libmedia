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
		
		Handler() = default;
		virtual ~Handler() = default;
		
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
	App() = default;
	virtual ~App() = default;
	
	virtual Graphics *getGraphics() = 0;
	virtual Pointer *getPointer() = 0;
	virtual Sensor *getSensor() = 0;
	
	virtual void setHandler(Handler *h) = 0;
	virtual Handler *getHandler() = 0;
};
}

#define MEDIA_SET_APP_HANDLER(__AppHandler__) \
	static __AppHandler__ __app_handler__; \
	media::App::Handler *__app_handler = &__app_handler__;
