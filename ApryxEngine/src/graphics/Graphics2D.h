#pragma once

#include <string>
#include <array>

#include "Paint.h"
#include "Sprite.h"
#include "math/Vector2.h"
#include "math/Vector4.h"

#include "math/Rectangle.h"

#include "graphics/Camera2D.h"

#include <stack>


namespace apryx {

	class Surface;

	class Graphics2D {
	public:
		// TODO engineer this
		virtual void save() = 0; // Save the state (current clipping and matrices)

		virtual void setCamera(Camera2D camera) = 0;
		virtual void clipRect(Rectanglef rectangle) = 0;
		virtual void reset() = 0;

		virtual void restore() = 0;

		virtual void drawRectangle(const Paint &paint, Rectanglef rectangle) = 0;
		virtual void drawLine(const Paint &paint, Vector2f pos1, Vector2f pos2) = 0;

		virtual void drawRoundedRectangle(const Paint &paint, Rectanglef rectangle, float roundingRadius) = 0;

		virtual void drawCircle(const Paint &paint, Vector2f center, float radius) = 0;
		virtual void drawElipse(const Paint &paint, Rectanglef rectangle) = 0;
		virtual void drawElipse(const Paint &paint, Vector2f center, float radiusx, float radiusy) = 0;
		virtual void drawArc(const Paint &paint, Vector2f center, float radius, float startAngle, float sweepAngle) = 0;
		virtual void drawArc(const Paint &paint, Vector2f center, float radiusx, float radiusy, float startAngle, float sweepAngle) = 0;

		// DEPRECATED
		virtual void drawSpiral(const Paint &paint, Vector2f center, float radiusStart, float radiusEnd, float startAngle, float sweepAngle) = 0;

		virtual void drawText(const Paint &paint, Vector2f pos, std::string text) = 0;

		virtual void drawSprite(const Paint &paint, const Sprite &sprite, Vector2f pos) = 0;
		virtual void drawSprite(const Paint &paint, const Sprite &sprite, Vector2f pos, Vector2f scale) = 0;
		virtual void drawSprite(const Paint &paint, const Sprite &sprite, Vector2f pos, Vector2f scale, float angle) = 0;

		virtual void drawSurface(const Paint &paint, const Surface &surface, Vector2f pos) = 0;
		virtual void drawSurface(const Paint &paint, const Surface &surface, Vector2f pos, Vector2f scale) = 0;
		virtual void drawSurface(const Paint &paint, const Surface &surface, Vector2f pos, Vector2f scale, float angle) = 0;

		void drawConsole(const Paint &background, const Paint &foreground);

		virtual void drawClear(Color32 color) = 0;
		virtual void drawClearDepth() = 0;

		virtual void flush() = 0;
	};

}