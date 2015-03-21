#pragma once

#include "platform.h"

#ifdef __MEDIA_ANDROID

#include "../media.h"
#include "../common/common.h"

#include <android_native_app_glue.h>
#include <android/sensor.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#define POINTER_MAX 0x40

struct __ivec2
{
	int x,y;
};

struct pointer
{
	int count;
	struct __ivec2 pos[POINTER_MAX];
	struct __ivec2 rel[POINTER_MAX];
};

typedef struct Media_PlatformContext 
{
	struct android_app* app;
	
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	int32_t width;
	int32_t height;
	
	int frame_counter;
	struct pointer pointer;
  
	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	ASensorEventQueue* sensorEventQueue;
}
Media_PlatformContext;

int _Media_initGraphics(Media_PlatformContext *engine);
void _Media_disposeGraphics(Media_PlatformContext *engine);

#endif
