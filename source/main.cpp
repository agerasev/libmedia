#include <media/media.hpp>

class GraphicsHandler : public media::Graphics::Handler {
public:
	virtual void create() override {
		logMessage("graphics created");
	}
	
	virtual void destroy() override {
		logMessage("graphics destroyed");
	}
	
	virtual void resize(int w, int h) override {
		logMessage("graphics resized %d %d", w, h);
	}
};

class AppHandler : public media::App::Handler {
public:
	virtual void create() override {
		super->getGraphics()->setHandler(new GraphicsHandler);
		logMessage("app created");
	}
	
	virtual void destroy() override {
		delete super->getGraphics()->getHandler();
		super->getGraphics()->setHandler(nullptr);
		logMessage("app destroyed");
	}
} app_handler;

MEDIA_SET_APP_HANDLER(&app_handler);
