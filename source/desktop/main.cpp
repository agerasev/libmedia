#include <media/media.hpp>

#include <SDL2/SDL.h>

#include "app.hpp"
#include "event.hpp"

#include <string>
#include <vector>

using namespace media;

extern App::Handler *__app_handler;
static DesktopApp *this_app;

int main(int argc, char *argv[]) {
	std::vector<std::string> args;
	for(int i = 0; i < argc; ++i) {
		args.push_back(argv[i]);
	}
	
	this_app = new DesktopApp();
	this_app->setHandler(__app_handler);
	this_app->create();
	
	bool done = false;
	while(!done) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			done = handle(this_app, event);
		}
	}
	
	this_app->destroy();
	delete this_app;
	return 0;
}
