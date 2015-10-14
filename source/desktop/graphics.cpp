#include <media/log.hpp>

#include "graphics.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>

using namespace media;

DesktopGraphics::DesktopGraphics()
{
	width = 800;
	height = 600;

	window = SDL_CreateWindow(
			"MediaApp",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);
	
	if(window == nullptr)
	{
		logWarning("Could not create SDL_Window\n");
		return;
	}
	
	context = SDL_GL_CreateContext(window);
	
	if(context == nullptr)
	{
		logWarning("Could not create SDL_GL_Context\n");
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetSwapInterval(1);

	GLenum glew_status = glewInit();
	if(GLEW_OK != glew_status)
	{
		logWarning("Could not init glew: %s\n", glewGetErrorString(glew_status));
		return;
	}
	if(!GLEW_VERSION_2_0)
	{
		logWarning("No support for OpenGL 2.0 found\n");
		return;
	}
	
	valid = true;
}

DesktopGraphics::~DesktopGraphics()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

ivec2 DesktopGraphics::getBounds() const {
	return ivec2(width, height);
}

bool DesktopGraphics::isValid() const {
	return valid;
}

void DesktopGraphics::create() {
	if(getHandler() != nullptr) {
		getHandler()->create();
	}
}

void DesktopGraphics::destroy() {
	if(getHandler() != nullptr) {
		getHandler()->destroy();
	}
}

void DesktopGraphics::resize() {
	if(getHandler() != nullptr) {
		ivec2 s = getBounds();
		getHandler()->resize(s.x(), s.y());
	}
}

void DesktopGraphics::resize(int w, int h) {
	width = w;
	height = h;
	resize();
}

SDL_Window *DesktopGraphics::getWindow() {
	return window;
}

SDL_GLContext DesktopGraphics::getGLContext() {
	return context;
}

void DesktopGraphics::setHandler(Handler *h) {
	handler = h;
	if(handler != nullptr) {
		handler->super = this;
	}
}

Graphics::Handler *DesktopGraphics::getHandler() const {
	return handler;
}
