#pragma once

#include <media/graphics.hpp>

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace media {
class DesktopGraphics : public Graphics {
private:
	int width, height;
	SDL_Window *window;
	SDL_GLContext context;
	bool valid = false;
	int lts = 0;
	
	Handler *handler = nullptr;
	
public:
	DesktopGraphics();
	virtual ~DesktopGraphics();
	
	virtual ivec2 getBounds() const override;
	
	bool isValid() const;
	
	void create();
	void destroy();
	void resize();
	void resize(int w, int h);
	void draw();
	
	SDL_Window *getWindow();
	SDL_GLContext getGLContext();
	
	virtual void setHandler(Handler *h) override;
	virtual Handler *getHandler() const override;
};
}
