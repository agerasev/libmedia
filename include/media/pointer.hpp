#pragma once

#include <la/vec.hpp>

namespace media {
class Pointer {
public:
	static const int
	  LEFT = 1,
	  RIGHT = 2,
		MIDDLE = 4;
	
	class Handler {
	public:
		Pointer *super = nullptr;
		
		Handler() = default;
		virtual ~Handler() = default;
		
		virtual void move(int buttons, ivec2 from, ivec2 to) {}
		virtual void up(int button, ivec2 pos, int index) {}
		virtual void down(int button, ivec2 pos, int index) {}
		virtual void click(int button, ivec2 pos, int index) {}
		virtual void scroll(ivec2 pos, ivec2 val) {}
	};
	
public:
	Pointer() = default;
	virtual ~Pointer() = default;
	
	virtual void setHandler(Handler *h) = 0;
	virtual Handler *getHandler() = 0;
	
	virtual ivec2 getPosition(int index = 0) const = 0;
	virtual int getButtons() const = 0;
};
}
