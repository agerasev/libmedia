#include "event.hpp"

bool handle(media::DesktopApp *app, const SDL_Event &event) {
	switch(event.type)
	{
	case SDL_QUIT:
		return true;
	case SDL_WINDOWEVENT:
		switch(event.window.event) 
		{
		case SDL_WINDOWEVENT_RESIZED:
			app->getGraphics()->resize(event.window.data1, event.window.data2);
			break;
		/* Not used due to bad behavior
		case SDL_WINDOWEVENT_MAXIMIZED:
			app->getHandler()->show();
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			app->getHandler()->hide();
			break;
		*/
		default:
			break;
		}
		break;
	/*
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
	*/
	default:
		break;
	}
	return false;
}
