#pragma once

#include <string>

class JSHandler {
private:
	std::string _name;
	
public:
	JSHandler(const std::string &name);
	virtual ~JSHandler();
};
