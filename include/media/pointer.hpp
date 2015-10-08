#pragma once

namespace media {
class Pointer {
public:
	class Handler {
		virtual void move() {}
		virtual void up() {}
		virtual void down() {}
		virtual void click() {}
		virtual void scroll(int x, int y) {}
	};
};
}
