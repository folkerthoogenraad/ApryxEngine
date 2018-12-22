#pragma once

#include "ui/ApryxUI.h"

#include "application/Application.h"

namespace apryx {

	class GUIApplication : public Application {
		ApryxUI ui;
	public:
		virtual void init(std::shared_ptr<Context> context) override;

		virtual void draw(Graphics2D &graphics) override;

		virtual void update() override;

		virtual void destroy() override;
	};
}