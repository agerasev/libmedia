#include "../media.h"
#include "common.h"

#include <stdlib.h>

#define PUSH_EVENT(app,handler,event) \
	int __i = 0; \
	for(__i = 0; __i < app->listeners_size; ++__i) { \
		app->listeners[__i]->handler(event,app->listeners[__i]->data); \
	}

void _Media_pushAppEvent(Media_App *app, const Media_AppEvent *event) 
{
	PUSH_EVENT(app,app,event)
}
void _Media_pushSurfaceEvent(Media_App *app, const Media_SurfaceEvent *event) 
{
	PUSH_EVENT(app,surface,event)
}
void _Media_pushMotionEvent(Media_App *app, const Media_MotionEvent *event) 
{
	PUSH_EVENT(app,motion,event)
}
void _Media_pushSensorEvent(Media_App *app, const Media_SensorEvent *event) 
{
	PUSH_EVENT(app,sensor,event)
}

void _Media_initApp(Media_App *app)
{
	app->listeners = NULL;
	app->listeners_size = 0;
	app->renderer = NULL;
	app->data = NULL;
	app->platform_context = NULL;
}

void _Media_freeApp(Media_App *app)
{
	if(app->listeners)
	{
		free(app->listeners);
		app->listeners_size = 0;
	}
}

void Media_addListener(Media_App *app, Media_Listener *listener)
{
	int i;
	int nn = app->listeners_size + 1;
	Media_Listener **nl = (Media_Listener**)malloc(sizeof(Media_Listener*)*nn);
	for(i = 0; i < app->listeners_size; ++i)
	{
		nl[i] = app->listeners[i];
	}
	nl[nn-1] = listener;
	
	if(app->listeners)
	{
		app->listeners_size = 0;
		free(app->listeners);
	}
	
	app->listeners = nl;
	app->listeners_size = nn;
}

void Media_removeListener(Media_App *app, Media_Listener *listener)
{
	int i;
	
	if(app->listeners_size <= 0)
	{
		return;
	}
	
	int found = 0;
	int pos;
	for(i = 0; i < app->listeners_size; ++i)
	{
		if(listener == app->listeners[i])
		{
			found = 1;
			pos = i;
			break;
		}
	}
	
	if(!found)
	{
		return;
	}
	
	int nn = app->listeners_size - 1;
	if(nn == 0)
	{
		app->listeners_size = 0;
		free(app->listeners);
		app->listeners = NULL;
		return;
	}
	
	Media_Listener **nl = (Media_Listener**)malloc(sizeof(Media_Listener*)*nn);
	for(i = 0; i < nn; ++i)
	{
		int j = i + (i >= pos);
		nl[i] = app->listeners[j];
	}
	
	app->listeners_size = 0;
	free(app->listeners);
	app->listeners = nl;
	app->listeners_size = nn;
}

void Media_setRenderer(Media_App *app, void (*renderer)(Media_App *))
{
	app->renderer = renderer;
}
