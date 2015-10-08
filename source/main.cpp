#include <media/media.hpp>

#include "app.hpp"

#include <string>
#include <vector>

#include <unistd.h>

extern media::App::Handler *__app_handler;
static media::DesktopApp this_app;

int main(int argc, char *argv[]) {
	std::vector<std::string> args;
	for(int i = 0; i < argc; ++i) {
		args.push_back(argv[i]);
	}
	this_app.setHandler(__app_handler);
	this_app.getHandler()->create(args);
	sleep(1);
	this_app.getHandler()->destroy();
	return 0;
}
