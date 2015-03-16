#ifndef __ANDROID__

#define DEBUG

#include "media.h"
#include "common.h"

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>

typedef struct PlatformContext
{
	SDL_Window *window;
	SDL_GLContext context;
	
	int width;
	int height;
	
	int mouse[3];
	
	int init_event_pushed;
}
PlatformContext;

static int getButtonNum(int button)
{
	if(button == SDL_BUTTON_LEFT)
	{
		return 0;
	}
	else
	if(button == SDL_BUTTON_MIDDLE)
	{
		return 1;
	}
	else
	if(button == SDL_BUTTON_RIGHT)
	{
		return 2;
	}
	return -1;
}

static const Media_ButtonType BUTTON[3] = { MEDIA_BUTTON_LEFT, MEDIA_BUTTON_MIDDLE, MEDIA_BUTTON_RIGHT };

int __initDisplay(PlatformContext *context)
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
#ifdef DEBUG
		printf("Could not create SDL_Window\n");
#endif
		return -1;
	}
	
	context->context = SDL_GL_CreateContext(context->window);
	
	if(context->context == NULL)
	{
#ifdef DEBUG
		printf("Could not create SDL_GL_Context\n");
#endif
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
#ifdef DEBUG
		printf("Could not init glew: %s\n",glewGetErrorString(glew_status));
#endif
		return -3;
	}
	if(!GLEW_VERSION_2_0)
	{
#ifdef DEBUG
		printf("No support for OpenGL 2.0 found\n");
#endif
		return -4;
	}
	
	return 0;
}

void __termDisplay(PlatformContext *context)
{
	SDL_GL_DeleteContext(context->context);
	SDL_DestroyWindow(context->window);
}

static void __handleEvent(Media_App *app, PlatformContext *context, const SDL_Event *event)
{
	Media_AppEvent app_event;
	Media_SurfaceEvent surface_event;
	Media_MotionEvent motion_event;
	if(!context->init_event_pushed)
	{
		surface_event.w = context->width;
		surface_event.h = context->height;
		surface_event.type = MEDIA_SURFACE_INIT;
		_Media_pushSurfaceEvent(app,&surface_event);
		surface_event.type = MEDIA_SURFACE_RESIZE;
		_Media_pushSurfaceEvent(app,&surface_event);
		context->init_event_pushed = 1;
	}
	
	switch(event->type)
	{
	case SDL_QUIT:
		surface_event.type = MEDIA_SURFACE_TERM;
		_Media_pushSurfaceEvent(app,&surface_event);
		app_event.type = MEDIA_APP_QUIT;
		_Media_pushAppEvent(app,&app_event);
		break;
	case SDL_WINDOWEVENT:
		switch(event->window.event) 
		{
		case SDL_WINDOWEVENT_RESIZED:
			context->width = event->window.data1;
			context->height = event->window.data2;
			surface_event.type = MEDIA_SURFACE_RESIZE;
			surface_event.w = context->width;
			surface_event.h = context->height;
			_Media_pushSurfaceEvent(app,&surface_event);
			break;
		/*
		// Not used due to bad behavior
		case SDL_WINDOWEVENT_MAXIMIZED:
			app_event.type = MEDIA_APP_SHOW;
			pushAppEvent(app,&app_event);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			app_event.type = MEDIA_APP_HIDE;
			pushAppEvent(app,&app_event);
			break;
		
		*/
		default:
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		motion_event.action = MEDIA_ACTION_MOVE;
		motion_event.button = 
		  MEDIA_BUTTON_LEFT*context->mouse[0] |
		  MEDIA_BUTTON_MIDDLE*context->mouse[1] |
		  MEDIA_BUTTON_RIGHT*context->mouse[2];
		motion_event.x = event->motion.x;
		motion_event.y = event->motion.y;
		_Media_pushMotionEvent(app,&motion_event);
		break;
	case SDL_MOUSEBUTTONDOWN:
		context->mouse[getButtonNum(event->button.button)] = 1;
		motion_event.action = MEDIA_ACTION_DOWN;
		motion_event.button = BUTTON[getButtonNum(event->button.button)];
		motion_event.x = event->button.x;
		motion_event.y = event->button.y;
		_Media_pushMotionEvent(app,&motion_event);
		break;
	case SDL_MOUSEBUTTONUP:
		context->mouse[getButtonNum(event->button.button)] = 0;
		motion_event.action = MEDIA_ACTION_UP;
		motion_event.button = BUTTON[getButtonNum(event->button.button)];
		motion_event.x = event->button.x;
	  motion_event.y = event->button.y;
		_Media_pushMotionEvent(app,&motion_event);
		break;
	case SDL_MOUSEWHEEL:
		motion_event.action = 0;
		motion_event.button = 0;
		motion_event.x = event->button.x;
	  motion_event.y = event->button.y;
		if(event->wheel.y > 0)
		{
			motion_event.action = MEDIA_ACTION_WHEEL_UP;
		}
		else
		if(event->wheel.y < 0)
		{
			motion_event.action = MEDIA_ACTION_WHEEL_DOWN;
		}
		if(motion_event.action)
		{
			_Media_pushMotionEvent(app,&motion_event);
		}
		break;
	default:
		break;
	}
}

void Media_handleEvents(Media_App *app)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		__handleEvent(app,(PlatformContext*)(app->platform_context),&event);
	}
}

void Media_waitForEvent(Media_App *app)
{
	SDL_Event event;
	if(SDL_WaitEvent(&event))
	{
		__handleEvent(app,(PlatformContext*)(app->platform_context),&event);
	}
}

void Media_renderFrame(Media_App *app)
{
	if(app->renderer != NULL)
	{
		app->renderer(app);
	}
	SDL_GL_SwapWindow(((PlatformContext*)(app->platform_context))->window);
}

int Media_enableSensor(Media_App *app, Media_SensorType type, unsigned long rate)
{
	return -1;
}

int Media_disableSensor(Media_App *app, Media_SensorType type)
{
	return -1;
}

int main(int argc, char *argv[])
{
	Media_App app;
	PlatformContext context;
	
	_Media_initApp(&app);
	
	context.mouse[0] = 0;
	context.mouse[1] = 0;
	context.mouse[2] = 0;
	
	context.init_event_pushed = 0;
	
	int returned_value;
	
	__initDisplay(&context);
	
	app.platform_context = (void*)&context;
	returned_value = Media_main(&app);
	
	__termDisplay(&context);
	
	_Media_freeApp(&app);
	
	return returned_value;
}

#endif
