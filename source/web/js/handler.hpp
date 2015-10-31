#pragma once

#include <string>

#include "canvas.hpp"

class JSHandler {
private:
	std::string _name;
	
public:
	JSHandler(JSCanvas *canvas);
	virtual ~JSHandler();
};
