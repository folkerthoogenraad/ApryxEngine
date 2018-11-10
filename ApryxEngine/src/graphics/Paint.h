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
		enum class HAlign {
			Left,
			Right,
			Center
		};
		enum class VAlign {
			Top,
			Bottom, 
			Center
		};
	private:
		Color32 m_Color;
		Style m_Style = Fill;

		HAlign m_HAlign = HAlign::Left;
		VAlign m_VAlign = VAlign::Top;

		float m_StrokeWidth = 1.0f;

		std::shared_ptr<Font> m_ButtonFont = nullptr;
	public:
		Paint();
		Paint(Color32 color);

		void setColor(Color32 c) { m_Color = c; }
		Color32 getColor() const { return m_Color; }

		Style getStyle() const { return m_Style; }
		void setStyle(Style style) { m_Style = style; }

		std::shared_ptr<Font> getFont() const { return m_ButtonFont; }
		void setFont(std::shared_ptr<Font> font) { m_ButtonFont = font; }

		float getStrokeWidth() const { return m_StrokeWidth; }
		void setStrokeWidth(float width) { m_StrokeWidth = width; }

		void setVerticalAlignment(VAlign align) { m_VAlign = align; }
		VAlign getVerticalAlignment() const { return m_VAlign; }

		void setHorizontalAlignment(HAlign align) { m_HAlign = align; }
		HAlign getHorizontalAlignment() const { return m_HAlign; }
	};

}