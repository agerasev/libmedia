#include "platform.h"

#ifdef __MEDIA_DESKTOP

#include "desktop.h"

#include <stdlib.h>

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

static void __handleEvent(Media_App *app, Media_PlatformContext *context, const SDL_Event *event)
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
	
	motion_event.index = 0;
	
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
		motion_event.x = event->motion.x - context->width/2;
		motion_event.y = context->height/2 - event->motion.y;
		motion_event.xval = event->motion.xrel;
		motion_event.yval = -event->motion.yrel;
		_Media_pushMotionEvent(app,&motion_event);
		break;
	case SDL_MOUSEBUTTONDOWN:
		context->mouse[getButtonNum(event->button.button)] = 1;
		motion_event.action = MEDIA_ACTION_DOWN;
		motion_event.button = BUTTON[getButtonNum(event->button.button)];
		motion_event.x = event->motion.x - context->width/2;
		motion_event.y = context->height/2 - event->motion.y;
		_Media_pushMotionEvent(app,&motion_event);
		break;
	case SDL_MOUSEBUTTONUP:
		context->mouse[getButtonNum(event->button.button)] = 0;
		motion_event.action = MEDIA_ACTION_UP;
		motion_event.button = BUTTON[getButtonNum(event->button.button)];
		motion_event.x = event->motion.x - context->width/2;
		motion_event.y = context->height/2 - event->motion.y;
		_Media_pushMotionEvent(app,&motion_event);
		break;
	case SDL_MOUSEWHEEL:
		motion_event.action = MEDIA_ACTION_WHEEL;
		motion_event.button = 0;
		motion_event.x = event->motion.x - context->width/2;
		motion_event.y = context->height/2 - event->motion.y;
		motion_event.xval = event->wheel.x;
		motion_event.yval = event->wheel.y;
		_Media_pushMotionEvent(app,&motion_event);
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
		__handleEvent(app,app->platform_context,&event);
	}
}

void Media_waitForEvent(Media_App *app)
{
	SDL_Event event;
	if(SDL_WaitEvent(&event))
	{
		__handleEvent(app,app->platform_context,&event);
	}
}

void Media_getPointer(Media_App *app, int *x, int *y)
{
	Media_PlatformContext* pc = app->platform_context;
	int mx, my;
	SDL_GetMouseState(&mx,&my);
	*x = mx - pc->width/2;
	*y = pc->height/2 - my;
}

void Media_getPointerByIndex(Media_App *app, int index, int *x, int *y)
{
	Media_getPointer(app,x,y);
}

int Media_getPointerCount(Media_App *app)
{
	Media_PlatformContext* pc = app->platform_context;
	return (pc->mouse[0] + pc->mouse[1] + pc->mouse[2]) > 0;
}

void Media_renderFrame(Media_App *app)
{
	if(app->renderer != NULL)
	{
		app->renderer(app);
	}
	SDL_GL_SwapWindow(app->platform_context->window);
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
	Media_PlatformContext context;
	
	_Media_initApp(&app);
	
	context.mouse[0] = 0;
	context.mouse[1] = 0;
	context.mouse[2] = 0;
	
	context.init_event_pushed = 0;
	
	int returned_value;
	
	_Media_initGraphics(&context);
	
	app.platform_context = &context;
	returned_value = Media_main(&app);
	
	_Media_disposeGraphics(&context);
	
	_Media_freeApp(&app);
	
	return returned_value;
}

#endif
