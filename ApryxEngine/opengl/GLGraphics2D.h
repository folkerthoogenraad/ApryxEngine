#pragma once

#include "graphics/Graphics2D.h"

#include "GLBatch.h"
#include "GLTexture.h"

namespace apryx {

	class GLGraphics2D : public Graphics2D{
	public:
		std::shared_ptr<GLTexture> m_WhiteTexture;

		float m_CirclePrecision = (3.141592654 * 2) / 36;

		GLBatch m_Batch;
	public:
		GLGraphics2D();

		virtual void setCamera(Camera2D camera);

		virtual void drawRectangle(Paint &paint, Rectanglef rectangle) override;
		virtual void drawLine(Paint &paint, Vector2f pos1, Vector2f pos2) override;

		virtual void drawRoundedRectangle(Paint &paint, Rectanglef rectangle, Rounding rounding) override;

		virtual void drawCircle(Paint &paint, Vector2f center, float radius) override;
		virtual void drawElipse(Paint &paint, Rectanglef rectangle) override;
		virtual void drawElipse(Paint &paint, Vector2f center, float radiusx, float radiusy) override;
		virtual void drawArc(Paint &paint, Vector2f center, float radius, float startAngle, float sweepAngle) override;
		virtual void drawArc(Paint &paint, Vector2f center, float radiusx, float radiusy, float startAngle, float sweepAngle) override;
		virtual void drawSpiral(Paint &paint, Vector2f center, float radiusStart, float radiusEnd, float startAngle, float sweepAngle) override;


		virtual void drawText(Paint &paint, Vector2f pos, std::string text) override;

		virtual void drawSprite(Paint &paint, Sprite &sprite, Vector2f pos) override;
		virtual void drawSprite(Paint &paint, Sprite &sprite, Vector2f pos, Vector2f scale) override;
		virtual void drawSprite(Paint &paint, Sprite &sprite, Vector2f pos, Vector2f scale, float angle) override;

		virtual void drawClear() override;

		virtual void flush();
	};

}