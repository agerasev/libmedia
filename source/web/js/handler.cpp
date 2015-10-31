#include "handler.hpp"

#include "utility.hpp"

JSHandler::JSHandler(JSCanvas *canvas) :
	_name(canvas->getName()) 
{
	eval("__libmediaAttachHandler(" + _name + ");");
}

JSHandler::~JSHandler() {
	
}
