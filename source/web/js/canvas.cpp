#include "canvas.hpp"

#include "utility.hpp"

JSCanvas::JSCanvas(const std::string &name) : 
  _name(name) 
{
	eval(_name + " = document.createElement('canvas');");
	eval(_name + ".innerHTML = 'HTML5 Canvas not supported';");
	eval("document.body.appendChild(" + _name + ");");
}

std::string JSCanvas::getName() const {
	return _name;
}

void JSCanvas::setBounds(int width, int height) {
	eval(_name + ".width = " + std::to_string(width) + ";");
	eval(_name + ".height = " + std::to_string(height) + ";");
}

ivec2 JSCanvas::getBounds() {
	int w, h;
	w = eval_int("return " + _name + ".width;");
	h = eval_int("return " + _name + ".height;");
	return ivec2(w, h);
}
