#pragma once

#include <media/graphics.hpp>

#include <exception>

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace media {
class DesktopGraphics : public Graphics {
private:
	SDL_Window *window;
	SDL_GLContext context;
	bool valid = false;
	
	Handler *handler;
	
public:
	DesktopGraphics();
	virtual ~DesktopGraphics();
	
	bool isValid() const;
	
	void create();
	void destroy();
	void resize();
	void resize(int w, int h);
	
	SDL_Window *getWindow();
	SDL_GLContext getGLContext();
	
	virtual void setHandler(Handler *h) override;
	virtual Handler *getHandler() const override;
};
}
