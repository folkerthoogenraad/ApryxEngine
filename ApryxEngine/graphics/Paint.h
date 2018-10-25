#pragma once

#include "math/Vector4.h"

#include "Font.h"

#include <memory>

namespace apryx {

	class Paint {
	public:
		enum Style{
			Fill,
			Stroke
		};
	private:
		Color32 m_Color;
		Style m_Style;

		float m_StrokeWidth = 1.0f;

		std::shared_ptr<Font> m_Font;
	public:
		Paint();
		Paint(Color32 color);

		void setColor(Color32 c) { m_Color = c; }
		Color32 getColor() const { return m_Color; }

		Style getStyle() const { return m_Style; }
		void setStyle(Style style) { m_Style = style; }

		std::shared_ptr<Font> getFont() const { return m_Font; }
		void setFont(std::shared_ptr<Font> font) { m_Font = font; }
	};

}