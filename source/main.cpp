#include <media/media.hpp>

class AppHandler : public media::App::Handler {
public:
	virtual void create() override {
		logMessage("app created");
	}
	
	virtual void destroy() override {
		logMessage("app destroyed");
	}
} app_handler;

MEDIA_SET_APP_HANDLER(&app_handler);
