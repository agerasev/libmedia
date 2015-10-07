#include <media/log.hpp>

#include "graphics.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>

int _Media_initGraphics(Media_PlatformContext *context)
{
	context->width = 800;
	context->height = 600;

	context->window = SDL_CreateWindow(
			"MediaApp",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			context->width, context->height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);
	
	if(context->window == NULL)
	{
		logWarning("Could not create SDL_Window\n");
		return -1;
	}
	
	context->context = SDL_GL_CreateContext(context->window);
	
	if(context->context == NULL)
	{
		logWarning("Could not create SDL_GL_Context\n");
		return -2;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
	SDL_GL_SetSwapInterval(1);

	GLenum glew_status = glewInit();
	if(GLEW_OK != glew_status)
	{
		logWarning("Could not init glew: %s\n",glewGetErrorString(glew_status));
		return -3;
	}
	if(!GLEW_VERSION_2_0)
	{
		logWarning("No support for OpenGL 2.0 found\n");
		return -4;
	}
	
	return 0;
}

void _Media_disposeGraphics(Media_PlatformContext *context)
{
	SDL_GL_DeleteContext(context->context);
	SDL_DestroyWindow(context->window);
}

