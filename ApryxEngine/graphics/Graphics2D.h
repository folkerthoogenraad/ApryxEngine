#pragma once

#include <string>
#include <array>

#include "Paint.h"
#include "Sprite.h"

#include "math/Vector2.h"
#include "math/Rectangle.h"

namespace apryx {

	typedef std::array<float, 4> Rounding;

	class Graphics2D {

	public:
		virtual void setSize(float width, float height) = 0;

		// Implementable interface
		virtual void drawRectangle(Paint &paint, Rectanglef rectangle) = 0;

		virtual void drawRoundedRectangle(Paint &paint, Rectanglef rectangle, Rounding rounding) = 0;

		virtual void drawCircle(Paint &paint, Vector2f center, float radius) = 0;
		virtual void drawElipse(Paint &paint, Rectanglef rectangle) = 0;
		virtual void drawElipse(Paint &paint, Vector2f center, float radiusx, float radiusy) = 0;
		virtual void drawArc(Paint &paint, Vector2f center, float radius, float startAngle, float sweepAngle) = 0;
		virtual void drawArc(Paint &paint, Vector2f center, float radiusx, float radiusy, float startAngle, float sweepAngle) = 0;
		virtual void drawSpiral(Paint &paint, Vector2f center, float radiusStart, float radiusEnd, float startAngle, float sweepAngle) = 0;

		virtual void drawText(Paint &paint, Vector2f pos, std::string text) = 0;

		virtual void drawSprite(Paint &paint, Sprite &sprite, Vector2f pos) = 0;
		virtual void drawSprite(Paint &paint, Sprite &sprite, Vector2f pos, Vector2f scale) = 0;
		virtual void drawSprite(Paint &paint, Sprite &sprite, Vector2f pos, Vector2f scale, float angle) = 0;

		virtual void drawClear() = 0;

		virtual void flush() = 0;
	};

}