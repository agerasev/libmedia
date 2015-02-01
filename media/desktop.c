#ifndef __ANDROID__

#include "media.h"

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>

struct __Context
{
	SDL_Window *window;
	SDL_GLContext context;
	
	int width;
	int height;
	
	int mouse[3];
	
	void(*app_func)    (const Media_AppEvent*,    void*);
	void(*surface_func)(const Media_SurfaceEvent*,void*);
	void(*motion_func) (const Media_MotionEvent*, void*);
	void(*sensor_func) (const Media_SensorEvent*, void*);
	void *listeners_data;
	
	int init_event_pushed;
	void(*renderer)(void*);
	void *renderer_data;
};
static struct __Context __context;

static void pushAppEvent(const Media_AppEvent *event) 
{
	if(__context.app_func) { __context.app_func(event,__context.listeners_data); }
}
static void pushSurfaceEvent(const Media_SurfaceEvent *event) 
{
	if(__context.surface_func) { __context.surface_func(event,__context.listeners_data); }
}
static void pushMotionEvent(const Media_MotionEvent *event) 
{
	if(__context.motion_func) { __context.motion_func(event,__context.listeners_data); }
}
static void pushSensorEvent(const Media_SensorEvent *event) 
{
	if(__context.sensor_func) { __context.sensor_func(event,__context.listeners_data); }
}

int Media_init()
{
	__context.width = 800;
	__context.height = 600;

	__context.window =
		SDL_CreateWindow(
			"MyNativeApp",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			__context.width, __context.height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);
	
	__context.context =
		SDL_GL_CreateContext(__context.window);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
	SDL_GL_SetSwapInterval(1);

	GLenum glew_status = glewInit();
	if(GLEW_OK != glew_status)
	{
		printf("%s\n",glewGetErrorString(glew_status));
		return -1;
	}
	if(!GLEW_VERSION_2_0)
	{
		printf("%s\n","No support for OpenGL 2.0 found");
		return -2;
	}
	
	return 0;
}

void Media_quit()
{
	SDL_GL_DeleteContext(__context.context);
	SDL_DestroyWindow(__context.window);
}

static void handleEvent(const SDL_Event *event)
{
	Media_AppEvent app_event;
	Media_SurfaceEvent surface_event;
	Media_MotionEvent motion_event;
	if(!__context.init_event_pushed)
	{
		surface_event.type = MEDIA_SURFACE_INIT;
		pushSurfaceEvent(&surface_event);
		surface_event.type = MEDIA_SURFACE_RESIZE;
		surface_event.width = __context.width;
		surface_event.height = __context.height;
		pushSurfaceEvent(&surface_event);
		__context.init_event_pushed = 1;
	}
	
	switch(event->type)
	{
	case SDL_QUIT:
		surface_event.type = MEDIA_SURFACE_TERM;
		pushSurfaceEvent(&surface_event);
		app_event.type = MEDIA_APP_QUIT;
		pushAppEvent(&app_event);
		break;
	case SDL_WINDOWEVENT:
		switch(event->window.event) 
		{
		case SDL_WINDOWEVENT_RESIZED:
			__context.width = event->window.data1;
			__context.height = event->window.data2;
			surface_event.type = MEDIA_SURFACE_RESIZE;
			surface_event.width = __context.width;
			surface_event.height = __context.height;
			pushSurfaceEvent(&surface_event);
			break;
		/*
		// Not used due to bad behavior
		case SDL_WINDOWEVENT_MAXIMIZED:
			app_event.type = MEDIA_APP_SHOW;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			app_event.type = MEDIA_APP_HIDE;
			break;
		
		*/
		default:
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		if(__context.mouse[0])
		{
			motion_event.type = MEDIA_MOTION;
			motion_event.action = MEDIA_ACTION_MOVE;
			motion_event.x = event->motion.x;
		  motion_event.y = event->motion.y;
			pushMotionEvent(&motion_event);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if(event->button.button == SDL_BUTTON_LEFT)
		{
			__context.mouse[0] = 1;
			motion_event.type = MEDIA_MOTION;
			motion_event.action = MEDIA_ACTION_DOWN;
			motion_event.x = event->button.x;
		  motion_event.y = event->button.y;
			pushMotionEvent(&motion_event);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if(event->button.button == SDL_BUTTON_LEFT)
		{
			__context.mouse[0] = 0;
			motion_event.type = MEDIA_MOTION;
			motion_event.action = MEDIA_ACTION_UP;
			motion_event.x = event->button.x;
		  motion_event.y = event->button.y;
			pushMotionEvent(&motion_event);
		}
		break;
	default:
		break;
	}
}

void Media_handleEvents()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		handleEvent(&event);
	}
}

void Media_waitForEvent()
{
	SDL_Event event;
	if(SDL_WaitEvent(&event))
	{
		handleEvent(&event);
	}
}

void Media_setEventListeners(
    void (*app_func)    (const Media_AppEvent*,    void*), 
    void (*surface_func)(const Media_SurfaceEvent*,void*), 
    void (*motion_func) (const Media_MotionEvent*, void*), 
    void (*sensor_func) (const Media_SensorEvent*, void*), 
    void *data
)
{
	__context.app_func = app_func;
	__context.surface_func = surface_func;
	__context.motion_func = motion_func;
	__context.sensor_func = sensor_func;
	__context.listeners_data = data;
}

void Media_setRenderer(void (*renderer)(void*), void *data)
{
	__context.renderer = renderer;
	__context.renderer_data = data;
}

void Media_renderFrame()
{
	if(__context.renderer != NULL)
	{
		__context.renderer(__context.renderer_data);
	}
	SDL_GL_SwapWindow(__context.window);
}

int Media_enableSensor(Media_SensorType type, unsigned long rate)
{
	return -1;
}

int Media_disableSensor(Media_SensorType type)
{
	return -1;
}

#endif
