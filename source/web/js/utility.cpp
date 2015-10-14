#include "utility.hpp"

void eval(const std::string &script) {
	emscripten_run_script(script.data());
}

int eval_int(const std::string &script) {
	return emscripten_run_script_int(script.data());
}

std::string eval_string(const std::string &script) {
	return std::string(emscripten_run_script_string(script.data()));
}

