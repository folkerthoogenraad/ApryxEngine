#pragma once

#include "application/Application.h"

namespace apryx {

	class Game : public Application{

	public:
		virtual void init(std::shared_ptr<ResourceManager> manager) = 0;
		virtual void draw(Graphics2D &graphics, float frame) = 0;
		virtual void update(float delta) = 0;
		virtual void destroy() = 0;

		virtual bool shouldRedraw() { return true; }
		virtual bool shouldQuit() { return false; }
	};

}