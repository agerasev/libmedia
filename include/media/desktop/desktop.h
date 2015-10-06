#pragma once

#include "platform.h"

#ifdef __MEDIA_DESKTOP

#include "../media.h"
#include "../common/common.h"

#include <SDL2/SDL.h>

typedef struct Media_PlatformContext
{
	SDL_Window *window;
	SDL_GLContext context;
	
	int width;
	int height;
	
	int mouse[3];
	
	int init_event_pushed;
}
Media_PlatformContext;

int _Media_initGraphics(Media_PlatformContext *context);
void _Media_disposeGraphics(Media_PlatformContext *context);

#endif
