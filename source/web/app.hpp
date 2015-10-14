#pragma once

#include <media/app.hpp>

#include "js/canvas.hpp"
#include "graphics.hpp"
#include "pointer.hpp"

namespace media {
class WebApp : public App {
private:
	JSCanvas jscanvas;
	WebGraphics graphics;
	WebPointer pointer;
	
	Handler *handler;
	
public:
	WebApp();
	virtual ~WebApp();
	
	void create();
	void destroy();
	
	JSCanvas *getCanvas();
	
	virtual WebGraphics *getGraphics() override;
	virtual WebPointer *getPointer() override;
	virtual Sensor *getSensor() override;
	
	virtual void setHandler(Handler *h) override;
	virtual Handler *getHandler() override;
};
}
