#pragma once

namespace media {
class Graphics {
public:
	class Listener {
	public:
		Graphics *super;
		virtual void create() {}
		virtual void destroy() {}
		virtual void resize(int, int) {}
	};
protected:
	Listener *listener = nullptr;
	int width = 0, height = 0;
	Graphics();
	Graphics(const Graphics &) = delete;
	Graphics &operator=(const Graphics &) = delete;
public:
	virtual ~Graphics() {}
	
	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}
	
	setListener(Listener *l) {
		listener = l;
		listener->super = this;
	}
	Listener *getListener() const {
		return listener;
	}
};
}
