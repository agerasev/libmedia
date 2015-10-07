#pragma once

#include <media/log.hpp>
#include <media/graphics.hpp>
#include <media/pointer.hpp>
#include <media/sensor.hpp>

#include <string>
#include <vector>

namespace media {
class App {
private:
	Graphics *graphics = nullptr;
	Pointer *pointer = nullptr;
	Sensor *sensor = nullptr;
	
	class Listener {
	public:
		App *super = nullptr;
		virtual void show() {}
		virtual void hide() {}
		virtual void saveState() {}
	};
	Listener *listener = nullptr;
	
	virtual void create() {}
	virtual void create(const std::vector<std::string> &) {
		create();
	}
	virtual void destroy() {}
};
}

#define MEDIA_SET_APP(AppDeriv) \
AppDeriv __global_app; \
media::App &this_app = __global_app;
