#pragma once

#include <media/app.hpp>
#include "graphics.hpp"

namespace media {
class DesktopApp : public App {
private:
	DesktopGraphics graphics;
	Handler *handler;
	
public:
	DesktopApp();
	virtual ~DesktopApp();
	
	void create();
	void destroy();
	
	virtual DesktopGraphics *getGraphics() override;
	virtual Pointer *getPointer() override;
	virtual Sensor *getSensor() override;
	
	virtual void setHandler(Handler *h) override;
	virtual Handler *getHandler() override;
};
}
