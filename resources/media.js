/* Mouse events */

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

function __libmediaContextMenu(e) {
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
	elem.oncontextmenu = __libmediaContextMenu;
	elem.onmousemove = __libmediaMouseMove;
}

/* Animation */

function __libmediaSuppressAnimation() {
	__libmedia_anim_suppressed = 1;
}

function __libmediaAllowAnimation() {
	__libmedia_anim_suppressed = 0;
}

function __libmediaStartAnimation() {
	if(__libmedia_anim_suppressed != 1) {
		window.requestAnimationFrame(__libmediaAnimate);
	}
}

function __libmediaForceAnimation() {
	window.requestAnimationFrame(__libmediaAnimate);
}

function __libmediaStopAnimation() {
	window.requestAnimationFrame(undefined);
}

function __libmediaAnimate(ts) {
	Module.ccall(
	  'libmedia_redraw_frame', null, 
	  ['number'], [ts]
	);
  window.requestAnimationFrame(__libmediaAnimate);
}

/* Loading custom scripts */

function __loadScript(file, callback)
{
	var head = document.getElementsByTagName('head')[0];
    var script = document.createElement('script');
    script.type = 'text/javascript';
    script.src = file;
    if(callback != undefined) {
		script.onreadystatechange = callback;
		script.onload = callback;
	}
	head.appendChild(script);
}

