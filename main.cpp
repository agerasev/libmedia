#include <media/media.h>
#include <graphics/graphics.h>

#include <stdlib.h>

struct State
{
	int done;
	int wait;
};

void handleEvent(const Media_Event *event, void *data)
{
	State *state = static_cast<State*>(data);
	switch(event->type)
	{
	case MEDIA_SAVE_STATE:
		printInfo("Save state\n");
		break;
	case MEDIA_QUIT:
		state->done = 1;
		printInfo("Quit\n");
		break;
	case MEDIA_SHOWN:
		state->wait = 0;
		printInfo("Shown\n");
		break;
	case MEDIA_HIDDEN:
		state->wait = 1;
		printInfo("Hidden\n");
		break;
	case MEDIA_INIT_SURFACE:
		printInfo("Init surface\n");
		initGraphics();
		break;
	case MEDIA_TERM_SURFACE:
		printInfo("Term surface\n");
		disposeGraphics();
		break;
	case MEDIA_RESIZE_SURFACE:
		printInfo("Resize surface ( %d, %d )\n",event->rect.x,event->rect.y);
		resizeGraphics(event->rect.x,event->rect.y);
		break;
	case MEDIA_MOTION:
		printInfo("Motion ( %d, %d )\n",event->rect.x,event->rect.y);
	default:
		break;
	}
}

void render(void *)
{
	clear();
	setColor(BLUE);
	circle();
}

int main()
{
	Media_init();
	
	int counter = 0;
	int time = 0;
	
	State state = {0,0};
	Media_setEventListener(handleEvent,static_cast<void*>(&state));
	
	Media_setRenderer(render,NULL);
	
	while(!state.done)
	{
		if(state.wait)
		{
			Media_waitForEvent();
		}
		Media_handleEvents();
		
		Media_renderFrame();
	}
	
	Media_quit();
	return 0;
}
