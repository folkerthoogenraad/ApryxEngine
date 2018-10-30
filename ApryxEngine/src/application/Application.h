#pragma once

#include "graphics/Graphics2D.h"

#include "resources/Context.h"

namespace apryx {

	class Application {

	public:
		virtual void init(std::shared_ptr<Context> context) = 0;
		virtual void draw(Graphics2D &graphics) = 0;
		virtual void update() = 0;
		virtual void destroy() = 0;

		virtual bool shouldRedraw() = 0;
		virtual bool shouldQuit() = 0;
	};

}