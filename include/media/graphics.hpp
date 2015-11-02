#pragma once

#include <la/vec.hpp>

namespace media {
class Graphics {
public:
	class Handler {
	public:
		Graphics *super;
		
		Handler() = default;
		virtual ~Handler() = default;
		
		virtual void create() {}
		virtual void destroy() {}
		virtual void resize(int, int) {}
		virtual void draw(double) {}
	};
	
public:
	Graphics() = default;
	virtual ~Graphics() = default;
	
	virtual ivec2 getBounds() const = 0;
	
	virtual void setHandler(Handler *l) = 0;
	virtual Handler *getHandler() const = 0;
};
}
