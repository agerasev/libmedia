/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "platform.h"

#ifdef __MEDIA_ANDROID

#include "android.h"

#include <jni.h>
#include <errno.h>

#include <android/log.h>

#define LOGI(...) (printInfo(__VA_ARGS__))
#define LOGW(...) (printWarn(__VA_ARGS__))

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* android_app, AInputEvent* event)
{
	int i;
	Media_App *app = (Media_App*)(android_app->userData);
	Media_PlatformContext *engine = app->platform_context;
	Media_MotionEvent motion_event;
	int32_t action;
	int index;
	
	switch(AInputEvent_getType(event))
	{
	case AINPUT_EVENT_TYPE_MOTION:
		switch(AInputEvent_getSource(event))
		{
		case AINPUT_SOURCE_TOUCHSCREEN:
			
			action = AKeyEvent_getAction(event);
			motion_event.index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
			index = motion_event.index;
			if(index >= POINTER_MAX)
			{
				index = POINTER_MAX - 1;
			}
			motion_event.button = MEDIA_BUTTON_LEFT;
			
			switch(action & AMOTION_EVENT_ACTION_MASK)
			{
			case AMOTION_EVENT_ACTION_DOWN:
				motion_event.action = MEDIA_ACTION_DOWN;
				break;
			case AMOTION_EVENT_ACTION_UP:
				motion_event.action = MEDIA_ACTION_UP;
				break;
			case AMOTION_EVENT_ACTION_POINTER_DOWN:
				motion_event.action = MEDIA_ACTION_DOWN;
				break;
			case AMOTION_EVENT_ACTION_POINTER_UP:
				motion_event.action = MEDIA_ACTION_UP;
				break;
			case AMOTION_EVENT_ACTION_MOVE:
				motion_event.action = MEDIA_ACTION_MOVE;
				break;
			}
			
			engine->pointer.count = AMotionEvent_getPointerCount(event);
			if(engine->pointer.count > POINTER_MAX)
			{
				engine->pointer.count = POINTER_MAX;
			}
			
			for(i = 0; i < engine->pointer.count; ++i)
			{
				int x, y;
				x = AMotionEvent_getX(event,i) - engine->width/2;
				y = engine->height/2 - AMotionEvent_getY(event,i);
				engine->pointer.rel[i].x = x - engine->pointer.pos[i].x;
				engine->pointer.rel[i].y = y - engine->pointer.pos[i].y;
				engine->pointer.pos[i].x = x;
				engine->pointer.pos[i].y = y;
			}
			/*
			if(motion_event.action == MEDIA_ACTION_DOWN)
			{
				engine->pointer.rel[index].x = 0;
				engine->pointer.rel[index].y = 0;
			}
			*/
			motion_event.x = engine->pointer.pos[motion_event.index].x;
			motion_event.y = engine->pointer.pos[motion_event.index].y;
			motion_event.xval = engine->pointer.rel[motion_event.index].x;
			motion_event.yval = engine->pointer.rel[motion_event.index].y;
			_Media_pushMotionEvent(app,&motion_event);
			
			break;
		}
		
		return 1;
	/*
	case AINPUT_EVENT_TYPE_KEY:
		// handle key input...
		return 1;
	*/
  }
  
	return 0;
}

static void __produce_motion_events(struct android_app* android_app)
{
	int i;
	Media_App *app = (Media_App*)(android_app->userData);
	Media_PlatformContext *engine = app->platform_context;
	Media_MotionEvent motion_event;
	motion_event.action = MEDIA_ACTION_MOVE;
	motion_event.button = MEDIA_BUTTON_LEFT;
	for(i = 1; i < engine->pointer.count; ++i)
	{
		motion_event.index = i;
		motion_event.x = engine->pointer.pos[i].x;
		motion_event.y = engine->pointer.pos[i].y;
		motion_event.xval = engine->pointer.rel[i].x;
		motion_event.yval = engine->pointer.rel[i].y;
		_Media_pushMotionEvent(app,&motion_event);
	}
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* android_app, int32_t cmd) 
{
	Media_App *app = (Media_App*)(android_app->userData);
	Media_PlatformContext *engine = app->platform_context;
	Media_AppEvent app_event;
	Media_SurfaceEvent surface_event;
#ifdef DEBUG
	printInfo("Command %d\n",cmd);
#endif
	switch(cmd) 
	{
	case APP_CMD_SAVE_STATE:
		app_event.type = MEDIA_APP_SAVESTATE;
		_Media_pushAppEvent(app,&app_event);
		break;
	case APP_CMD_INIT_WINDOW:
		_Media_initGraphics(engine);
		surface_event.w = engine->width;
		surface_event.h = engine->height;
		surface_event.type = MEDIA_SURFACE_INIT;
		_Media_pushSurfaceEvent(app,&surface_event);
		surface_event.type = MEDIA_SURFACE_RESIZE;
		_Media_pushSurfaceEvent(app,&surface_event);
		break;
	case APP_CMD_TERM_WINDOW:
		_Media_disposeGraphics(engine);
		surface_event.type = MEDIA_SURFACE_TERM;
		_Media_pushSurfaceEvent(app,&surface_event);
		break;
	case APP_CMD_CONFIG_CHANGED:
		engine->frame_counter = 4;
	case APP_CMD_GAINED_FOCUS:
		app_event.type = MEDIA_APP_SHOW;
		_Media_pushAppEvent(app,&app_event);
		break;
	case APP_CMD_LOST_FOCUS:
		app_event.type = MEDIA_APP_HIDE;
		_Media_pushAppEvent(app,&app_event);
		break;
	case APP_CMD_DESTROY:
		app_event.type = MEDIA_APP_QUIT;
		_Media_pushAppEvent(app,&app_event);
		break;
	default:
		break;
	}
}

static void engine_handle_events(Media_App *app, int mode)
{
	Media_PlatformContext *engine = app->platform_context;
	if(engine->frame_counter > 0)
	{
		engine->frame_counter--;
		if(engine->frame_counter == 0)
		{
			Media_SurfaceEvent event;
			event.type = MEDIA_SURFACE_RESIZE;
			
			eglQuerySurface(engine->display, engine->surface, EGL_WIDTH, &(engine->width));
			eglQuerySurface(engine->display, engine->surface, EGL_HEIGHT, &(engine->height));
			event.w = engine->width;
			event.h = engine->height;
			_Media_pushSurfaceEvent(app,&event);
		}
	}
	
	// Read all pending events.
	int ident;
	int events;
	struct android_poll_source* source;

	// If not animating, we will block forever waiting for events.
	// If animating, we loop until all events are read, then continue
	// to draw the next frame of animation.
	while((ident=ALooper_pollAll(mode, NULL, &events, (void**)&source)) >= 0)
	{
		// LOGI("poll mode %d\n",mode);
	
		// Process this event.
		if(source != NULL) 
		{
			source->process(engine->app, source);
		}
		
		if(mode)
		{
			break;
		}
		
		// If a sensor has data, process it now.
		if (ident == LOOPER_ID_USER) 
		{
			if (engine->accelerometerSensor != NULL) 
			{
				Media_SensorEvent sensor_event;
				ASensorEvent event;
				while(ASensorEventQueue_getEvents(engine->sensorEventQueue,&event,1) > 0) 
				{
					sensor_event.sensor = MEDIA_SENSOR_ACCELEROMETER;
					sensor_event.x = event.acceleration.x;
					sensor_event.y = event.acceleration.y;
					sensor_event.z = event.acceleration.z;
					_Media_pushSensorEvent(app,&sensor_event);
				}
			}
		}
		
		__produce_motion_events(engine->app);
		
		// Check if we are exiting.
		if(engine->app->destroyRequested != 0) 
		{
			break;
		}
	}
}

void Media_handleEvents(Media_App *app)
{
	engine_handle_events(app,0);
}

void Media_waitForEvent(Media_App *app)
{
	engine_handle_events(app,-1);
}

void Media_getPointer(Media_App *app, int *x, int *y)
{
	Media_PlatformContext *engine = app->platform_context;
	*x = engine->pointer.pos[0].x;
	*y = engine->pointer.pos[0].y;
}

void Media_getPointerByIndex(Media_App *app, int index, int *x, int *y)
{
	Media_PlatformContext *engine = app->platform_context;
	if(index >= POINTER_MAX)
	{
		return;
	}
	*x = engine->pointer.pos[index].x;
	*y = engine->pointer.pos[index].y;
}

int Media_getPointerCount(Media_App *app)
{
	return app->platform_context->pointer.count;
}

void Media_renderFrame(Media_App *app)
{
	Media_PlatformContext *engine = app->platform_context;
	if(engine->display == NULL) 
	{
		// No display.
		return;
	}
	if(app->renderer != NULL)
	{
		app->renderer(app);
	}
	eglSwapBuffers(engine->display, engine->surface);
}

int Media_enableSensor(Media_App *app, Media_SensorType type, unsigned long rate)
{
	Media_PlatformContext *engine = app->platform_context;
	if(type == MEDIA_SENSOR_ACCELEROMETER && engine->accelerometerSensor != NULL) 
	{
		ASensorEventQueue_enableSensor(engine->sensorEventQueue,engine->accelerometerSensor);
		ASensorEventQueue_setEventRate(engine->sensorEventQueue,engine->accelerometerSensor,rate);
		return 0;
	}
	return -1;
}

int Media_disableSensor(Media_App *app, Media_SensorType type)
{
	Media_PlatformContext *engine = app->platform_context;
	if(type == MEDIA_SENSOR_ACCELEROMETER && engine->accelerometerSensor != NULL) 
	{
		ASensorEventQueue_disableSensor(engine->sensorEventQueue,engine->accelerometerSensor);
		return 0;
	}
	return -1;
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) 
{
	Media_App app;
	Media_PlatformContext engine;
	
	// Make sure glue isn't stripped.
	app_dummy();
	
	_Media_initApp(&app);
	
	memset(&engine,0,sizeof(Media_PlatformContext));
	state->userData = &app;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;
	engine.app = state;
	
	app.platform_context = &engine;
	
	// Prepare to monitor accelerometer
  engine.sensorManager = ASensorManager_getInstance();
  engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,ASENSOR_TYPE_ACCELEROMETER);
  engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,state->looper, LOOPER_ID_USER, NULL, NULL);
	
	Media_main(&app);
	
	_Media_freeApp(&app);
}

#endif
