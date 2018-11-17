#pragma once

#include <stack>

#include "graphics/Window.h"
#include "graphics/Graphics2D.h"

#include "GLBatch.h"

#include "math/Rectangle.h"


namespace apryx {

	class GLSurface;
	class GLTexture;

	class GLGraphics2D : public Graphics2D{
	public:
		std::shared_ptr<GLTexture> m_WhiteTexture;

		std::shared_ptr<Window> m_Window; // TODO make window a surface too.
		std::shared_ptr<GLSurface> m_Surface;

		std::stack<Matrix4f> m_MatrixStack;

		float m_CirclePrecision = (3.141592654f * 2) / 36;

		GLBatch m_Batch;
	public:
		GLGraphics2D(std::shared_ptr<Window> window);
		GLGraphics2D(std::shared_ptr<GLSurface> surface);
		
		virtual void save() override; // Save the state (current clipping and camera)
		
		virtual void setMatrix(Matrix4f matrix) override;
		virtual Matrix4f getMatrix() override;

		virtual void translate(Vector2f translation) override;
		virtual void scale(Vector2f scale) override;
		virtual void rotate(float amountInDegrees) override;

		virtual void clipRect(Rectanglef rectangle) override;
		virtual void reset() override;
		virtual void restore() override;

		virtual void drawRectangle(const Paint &paint, Rectanglef rectangle) override;
		virtual void drawLine(const Paint &paint, Vector2f pos1, Vector2f pos2) override;

		virtual void drawRoundedRectangle(const Paint &paint, Rectanglef rectangle, float roundingRadius) override;

		virtual void drawCircle(const Paint &paint, Vector2f center, float radius) override;
		virtual void drawElipse(const Paint &paint, Rectanglef rectangle) override;
		virtual void drawElipse(const Paint &paint, Vector2f center, float radiusx, float radiusy) override;
		virtual void drawArc(const Paint &paint, Vector2f center, float radius, float startAngle, float sweepAngle) override;
		virtual void drawArc(const Paint &paint, Vector2f center, float radiusx, float radiusy, float startAngle, float sweepAngle) override;
		
		virtual void drawSpiral(const Paint &paint, Vector2f center, float radiusStart, float radiusEnd, float startAngle, float sweepAngle) override;
		
		virtual void drawText(const Paint &paint, Vector2f pos, const std::string &text, Vector2f scale) override;

		virtual void drawSprite(const Paint &paint, const Sprite &sprite, Vector2f pos) override;
		virtual void drawSprite(const Paint &paint, const Sprite &sprite, Vector2f pos, Vector2f scale) override;
		virtual void drawSprite(const Paint &paint, const Sprite &sprite, Vector2f pos, Vector2f scale, float angle) override;

		virtual void drawSurface(const Paint &paint, const Surface &surface, Vector2f pos) override;
		virtual void drawSurface(const Paint &paint, const Surface &surface, Vector2f pos, Vector2f scale) override;
		virtual void drawSurface(const Paint &paint, const Surface &surface, Vector2f pos, Vector2f scale, float angle) override;

		virtual void drawClear(Color32 color) override;
		virtual void drawClearDepth() override;

		virtual void flush();
	};

}