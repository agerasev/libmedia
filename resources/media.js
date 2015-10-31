function __getEventX(e) {
	return e.offsetX == undefined ? e.layerX : e.offsetX; 
}

function __getEventY(e) {
	return e.offsetY == undefined ? e.layerY : e.offsetY;
}

function __libmediaMouseDown(e) {
	Module.ccall(
	  'libmedia_pointer_down', null, 
	  ['number', 'number', 'number'], 
	  [__getEventX(e), __getEventY(e), e.button]
	);
}

function __libmediaMouseUp(e) {
	Module.ccall(
	  'libmedia_pointer_up', null, 
	  ['number', 'number', 'number', 'number'], 
	  [__getEventX(e), __getEventY(e), e.button]
	);
}

function __libmediaClick(e) {
	Module.ccall(
	  'libmedia_pointer_click', null, 
	  ['number', 'number', 'number'], 
	  [__getEventX(e), __getEventY(e), 0]
	);
}

function __libmediaContextMenu(e) {
	Module.ccall(
	  'libmedia_pointer_click', null, 
	  ['number', 'number', 'number'], 
	  [__getEventX(e), __getEventY(e), 2]
	);
	e.preventDefault();
	return false;
}

function __libmediaMouseMove(e) {
	Module.ccall(
		'libmedia_pointer_move', null, 
		['number', 'number', 'number', 'number'], 
		[__getEventX(e), __getEventY(e), e.movementX, e.movementY]
	);
}

function __libmediaAttachHandler(elem) {
	elem.onmousedown = __libmediaMouseDown;
	elem.onmouseup = __libmediaMouseUp;
	elem.onclick = __libmediaClick;
	elem.oncontextmenu = __libmediaContextMenu;
	elem.onmousemove = __libmediaMouseMove;
}
