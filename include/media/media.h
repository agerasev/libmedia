#pragma once

#include "desktop/platform.h"

#include "log.h"
#include "event.h"
#include "input.h"
#include "assets.h"

typedef struct Media_PlatformContext Media_PlatformContext;

typedef struct Media_App
{
	void(*renderer)(Media_App*);
	
	Media_Listener **listeners;
	int listeners_size;
	
	/* User data */
	void *data;
	
	/* Platform-specific data */
	Media_PlatformContext *platform_context;
}
Media_App;

#ifdef __cplusplus
extern "C" {
#endif

/* Sets current renderer */
void Media_setRenderer(Media_App *app, void(*renderer)(Media_App *app));

/* Wraps user-defined app->renderer function */
void Media_renderFrame(Media_App *app);

/* Entry point for program
 * Must be implemented */
int Media_main(Media_App *app);

#ifdef __cplusplus
}
#endif


