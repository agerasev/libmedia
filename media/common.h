#pragma once

#include "media.h"

void _Media_initApp(Media_App *app);
void _Media_freeApp(Media_App *app);

void _Media_pushAppEvent(Media_App *app, const Media_AppEvent *event);
void _Media_pushSurfaceEvent(Media_App *app, const Media_SurfaceEvent *event);
void _Media_pushMotionEvent(Media_App *app, const Media_MotionEvent *event);
void _Media_pushSensorEvent(Media_App *app, const Media_SensorEvent *event);
