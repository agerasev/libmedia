#pragma once

typedef unsigned int Media_EventType;
typedef unsigned int Media_EventMask;

/* Event types */
#define MEDIA_APP_QUIT         0x0101
#define MEDIA_APP_SHOW         0x0105
#define MEDIA_APP_HIDE         0x0106
#define MEDIA_APP_SAVESTATE    0x0108

#define MEDIA_SURFACE_INIT     0x0202
#define MEDIA_SURFACE_TERM     0x0203
#define MEDIA_SURFACE_RESIZE   0x0204

#define MEDIA_MOTION           0x0400

#define MEDIA_SENSOR           0x0800

/* Event mask */
#define MEDIA_APP_MASK         0x0100
#define MEDIA_SURFACE_MASK     0x0200
#define MEDIA_MOTION_MASK      0x0400
#define MEDIA_SENSOR_MASK      0x0800

#include "motion.h"
#include "sensor.h"

typedef struct Media_Event
{
	Media_EventType type;
} 
Media_Event;

typedef struct Media_AppEvent
{
	Media_EventType type;
} 
Media_AppEvent;

typedef struct Media_SurfaceEvent
{
	Media_EventType type;
	int width, height;
} 
Media_SurfaceEvent;

typedef struct Media_MotionEvent
{
	Media_EventType type;
	Media_ActionType action;
	int index;
	int x,y;
} 
Media_MotionEvent;

typedef struct Media_SensorEvent
{
	Media_EventType type;
	Media_SensorType sensor;
	double x,y,z;
} 
Media_SensorEvent;

#ifdef __cplusplus
extern "C" {
#endif

void Media_setEventListeners(
    void (*app_func)    (const Media_AppEvent*,    void*), 
    void (*surface_func)(const Media_SurfaceEvent*,void*), 
    void (*motion_func) (const Media_MotionEvent*, void*), 
    void (*sensor_func) (const Media_SensorEvent*, void*), 
    void *data
);

void Media_handleEvents();
void Media_waitForEvent();

#ifdef __cplusplus
}
#endif
