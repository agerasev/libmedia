#include <media/media.hpp>

#include <emscripten.h>

#include "app.hpp"

using namespace media;

extern App::Handler *__app_handler;
WebApp *__app;

extern "C" {

void libmedia_start_app() {
	__app = new WebApp();
	__app->setHandler(__app_handler);
	__app->create();
}

void libmedia_stop_app() {
	__app->destroy();
	delete __app;
}

}

int main(int, char *[]) {
	libmedia_start_app();
	return 0;
}
