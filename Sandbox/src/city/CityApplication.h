#pragma once

#include <vector>

#include "application/Application.h"

#include "math/LineSegment2.h"

namespace apryx {

	class CityApplication : public Application {
		std::vector<LineSegment2f> lines;
		int generations;
	public:
		virtual void init(std::shared_ptr<Context> context) override;

		virtual void draw(Graphics2D &graphics) override;

		virtual void update() override;

		virtual void destroy() override;
		
		void doStuff();
	};
}