#include <media/media.hpp>

class MyApp : public media::App {
public:
	virtual void create() override {
		logMessage("app created");
	}
	
	virtual void destroy() override {
		logMessage("app destroyed");
	}
};

MEDIA_SET_APP(MyApp)
