#pragma once

#include <memory>

#include "resources/Context.h"

#include "math/Vector4.h"

#include "graphics/Font.h"
#include "graphics/Graphics2D.h"

namespace apryx {

	struct ApryxUIStyle {
		Color32 foreground = Color32::gray();
		Color32 background = Color32::white();

		Color32 primary = Color32(128, 160, 128, 255);
		Color32 contrast = Color32::white();

		std::shared_ptr<Font> textFont;
		std::shared_ptr<Font> componentFont;
	};

	class UIComponent;

	class ApryxUI {
		std::shared_ptr<Context> m_Context;

		// TODO component layers and shit
		std::shared_ptr<UIComponent> m_MainComponent;

		ApryxUIStyle m_Style;
	public:
		ApryxUI(std::shared_ptr<Context> context) : m_Context(context) { };

		void update();
		void draw(Graphics2D &graphics);

		float getDPIScale() const { return m_Context->getWindow()->dpiScale(); }

		void updateLayout(float width, float height);

		void setMainComponent(std::shared_ptr<UIComponent> component);

		const ApryxUIStyle &getStyle() const { return m_Style; }
		ApryxUIStyle &getStyle() { return m_Style; }
	public: 
		// Getters and setters
		std::shared_ptr<Context> getContext() { return m_Context; }
	};

}