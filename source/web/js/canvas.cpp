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

void JSCanvas::setBounds(int w, int h) {
	width = w;
	height = h;
	eval(_name + ".width = " + std::to_string(width) + ";");
	eval(_name + ".height = " + std::to_string(height) + ";");
}

ivec2 JSCanvas::getBounds() {
	return ivec2(width, height);
}

void JSCanvas::startAnimation() {
	eval("window.requestAnimationFrame(__libmediaAnimate);");
}

void JSCanvas::stopAnimation() {
	eval("window.requestAnimationFrame(null);");
}
