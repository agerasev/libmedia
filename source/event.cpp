#include "event.hpp"

using namespace media;

static int getButton(int sdl_button)
{
	switch(sdl_button) {
	case SDL_BUTTON_LEFT:
		return Pointer::LEFT;
	case SDL_BUTTON_MIDDLE:
		return Pointer::MIDDLE;
	case SDL_BUTTON_RIGHT:
		return Pointer::RIGHT;
	default:
		return 0;
	}
}

static ivec2 getPos(DesktopApp *app, ivec2 sdl_pos) {
	ivec2 bounds = app->getGraphics()->getBounds();
	return ivec2(
	      sdl_pos.x() - bounds.x()/2, 
	      bounds.y()/2 - sdl_pos.y()
	      );
}

bool handle(DesktopApp *app, const SDL_Event &event) {
	switch(event.type) {
	case SDL_QUIT:
		return true;
	case SDL_WINDOWEVENT:
		switch(event.window.event) {
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
	case SDL_MOUSEMOTION: {
		ivec2 pos = getPos(app, ivec2(event.motion.x, event.motion.y));
		ivec2 rel(event.motion.xrel, -event.motion.yrel);
		app->getPointer()->move(pos - rel, pos);
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
		app->getPointer()->down(
		      getButton(event.button.button),
		      getPos(app, ivec2(event.motion.x, event.motion.y))
		      );
		break;
	case SDL_MOUSEBUTTONUP:
		app->getPointer()->up(
		      getButton(event.button.button),
		      getPos(app, ivec2(event.motion.x, event.motion.y))
		      );
		break;
	case SDL_MOUSEWHEEL:
		app->getPointer()->scroll(
		      getPos(app, ivec2(event.motion.x, event.motion.y)),
		      ivec2(event.wheel.x, event.wheel.y)
		      );
		break;
	default:
		break;
	}
	return false;
}
