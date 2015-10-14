#pragma once

#include <emscripten.h>
#include <string>

// js evaluation
void eval(const std::string &script);
int eval_int(const std::string &script);
std::string eval_string(const std::string &script);
