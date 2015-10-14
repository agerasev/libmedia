#include "handler.hpp"

#include "utility.hpp"

JSHandler::JSHandler(const std::string &name) :
	_name(name) 
{
	eval("__libmedia_pointer_down = function(e) { "
	     "var x = e.offsetX == undefined ? e.layerX : e.offsetX; var y = e.offsetY == undefined ? e.layerY : e.offsetY;"
	     "Module.ccall('libmedia_pointer_down',null,['number','number','number'],[x,y,e.button]);"
	     "}");
	eval(_name + ".onmousedown = __libmedia_pointer_down;");
	eval("__libmedia_pointer_up = function(e) { "
	     "var x = e.offsetX == undefined ? e.layerX : e.offsetX; var y = e.offsetY == undefined ? e.layerY : e.offsetY;"
	     "Module.ccall('libmedia_pointer_up',null,['number','number','number','number'],[x,y,e.button]);"
	     "}");
	eval(_name + ".onmouseup = __libmedia_pointer_up;");
	
	eval("__libmedia_pointer_click = function(e) { "
	     "var x = e.offsetX == undefined ? e.layerX : e.offsetX; var y = e.offsetY == undefined ? e.layerY : e.offsetY;"
	     "Module.ccall('libmedia_pointer_click',null,['number','number','number'],[x,y,0]);"
	     "}");
	eval(_name + ".onclick = __libmedia_pointer_click;");
	eval("__libmedia_pointer_click = function(e) { "
	     "var x = e.offsetX == undefined ? e.layerX : e.offsetX; var y = e.offsetY == undefined ? e.layerY : e.offsetY;"
	     "Module.ccall('libmedia_pointer_click',null,['number','number','number'],[x,y,2]);"
	     "}");
	eval(_name + ".oncontextmenu = __libmedia_pointer_click;");
	
	eval("__libmedia_pointer_move = function(e) { "
	     "var x = e.offsetX == undefined ? e.layerX : e.offsetX; var y = e.offsetY == undefined ? e.layerY : e.offsetY;"
	     "Module.ccall('libmedia_pointer_move',null,['number','number','number','number'],[x,y,e.movementX,e.movementY]);"
	     "}");
	eval(_name + ".onmousemove = __libmedia_pointer_move;");
}

JSHandler::~JSHandler() {
	
}
