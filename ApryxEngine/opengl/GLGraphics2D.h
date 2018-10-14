#pragma once

#include "graphics/Graphics2D.h"

#include "GLBatch.h"
#include "GLTexture.h"

namespace apryx {

	class GLGraphics2D : Graphics2D{
		std::shared_ptr<GLTexture> m_WhiteTexture;

		GLBatch m_Batch;
	public:
		GLGraphics2D();

		virtual void setSize(float width, float height);

		virtual void drawRectangle(Paint &paint, Rectanglef rectangle) override;

		virtual void drawElipse(Paint &paint, Rectanglef rectangle) override;
		virtual void drawRoundedRectangle(Paint &paint, Rectanglef rectangle, Rounding rounding) override;

		virtual void drawArc(Paint &paint, Vector2f center, float radius, float startAngle, float sweepAngle) override;

		virtual void drawText(Paint &paint, Vector2f pos, std::string text) override;

		virtual void drawSprite(Paint &paint, Sprite &sprite, Vector2f pos) override;
		virtual void drawSprite(Paint &paint, Sprite &sprite, Vector2f pos, Vector2f scale) override;
		virtual void drawSprite(Paint &paint, Sprite &sprite, Vector2f pos, Vector2f scale, float angle) override;

		virtual void drawClear() override;

		virtual void flush();
	};

}