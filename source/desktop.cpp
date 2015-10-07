#include <media/media.hpp>

#include <string>
#include <vector>

extern media::App &this_app;

int main(int argc, char *argv[]) {
	std::vector<std::string> args;
	for(int i = 0; i < argc; ++i) {
		args.push_back(argv[i]);
	}
	this_app.create(args);
	this_app.destroy();
	return 0;
}
