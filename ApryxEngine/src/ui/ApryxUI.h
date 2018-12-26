#pragma once

#include <memory>

#include "resources/Context.h"

#include "math/Vector4.h"

#include "graphics/Font.h"
#include "graphics/Graphics2D.h"

namespace apryx {

	struct ApryxUIStyle {
		Color32 foreground = Color32(50, 50, 50, 255);
		Color32 background = Color32::white();

		Color32 primary = Color32(128, 160, 128, 255);
		Color32 primaryPressed = Color32(100, 128, 100, 255);

		Color32 contrast = Color32::white();

		Color32 inactive = Color32(200, 200, 200, 255);

		Color32 selection = Color32(128, 160, 128, 128);

		std::shared_ptr<Font> textFont;
		std::shared_ptr<Font> componentFont;
	};

	class UIComponent;

	class ApryxUI {
		std::shared_ptr<Context> m_Context;

		// TODO component layers and shit
		std::shared_ptr<UIComponent> m_MainComponent;

		std::weak_ptr<UIComponent> m_FocusComponent;
		std::weak_ptr<UIComponent> m_HoverComponent;

		ApryxUIStyle m_Style;


		// Keeping what components are pressed with what mouse button
		std::array<std::shared_ptr<UIComponent>, 3> m_PressedComponents;

		// Keeping the old mouse position so that we can update it correctly
		Vector2f m_MousePosition;

		bool m_Redraw = false;
	public:
		void init(std::shared_ptr<Context> context) { m_Context = context; };
		
		void draw(Graphics2D &graphics);

		float getDPIScale() const { return m_Context->getWindow()->dpiScale(); }

		void updateLayout(float width, float height);

		bool shouldRedraw() const { return m_Redraw; }
		void redraw() { m_Redraw = true; }

		void processEvents(const std::vector<InputEvent> &events);

		void setMainComponent(std::shared_ptr<UIComponent> component);

		std::shared_ptr<UIComponent> getComponentAtPosition(Vector2f position);

		const ApryxUIStyle &getStyle() const { return m_Style; }
		ApryxUIStyle &getStyle() { return m_Style; }
		void setStyle(ApryxUIStyle style) { m_Style = style; }
	private:
		void update();
	public: 
		
		// Getters and setters
		std::shared_ptr<Context> getContext() { return m_Context; }
	};

}