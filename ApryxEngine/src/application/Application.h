#pragma once

#include "graphics/Graphics2D.h"

#include "resources/ResourceManager.h"

namespace apryx {

	class Application {

	public:
		virtual void init(std::shared_ptr<ResourceManager> manager) = 0;
		virtual void draw(Graphics2D &graphics, float frame) = 0;
		virtual void update(float delta) = 0;
		virtual void destroy() = 0;

		virtual bool shouldRedraw() = 0;
		virtual bool shouldQuit() = 0;
	};

}