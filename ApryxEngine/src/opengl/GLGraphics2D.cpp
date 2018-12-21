#include "GLGraphics2D.h"

#include "graphics/Image.h"
#include "opengl/GL.h"

#include "math/Matrix3.h"
#include "math/math.h"

#include "GLSurface.h"
#include "GLTexture.h"

#include <assert.h>

namespace apryx {

	// TODO make this better (no duplicate code)
	GLGraphics2D::GLGraphics2D(std::shared_ptr<Window> window)
		: m_Window(window)
	{
		assert(window != nullptr);

		Image image = Image::colored(1, 1);

		m_WhiteTexture = std::make_shared<GLTexture>();
		m_WhiteTexture->setData(image);

		m_Batch.texture(m_WhiteTexture);

		m_MatrixStack.push(Matrix4f::identity());
		reset();
	}
	GLGraphics2D::GLGraphics2D(std::shared_ptr<GLSurface> surface)
		: m_Surface(surface)
	{
		assert(surface != nullptr);
		Image image = Image::colored(1, 1);

		m_WhiteTexture = std::make_shared<GLTexture>();
		m_WhiteTexture->setData(image);

		m_Batch.texture(m_WhiteTexture);

		m_MatrixStack.push(Matrix4f::identity());
		reset();
	}

	void GLGraphics2D::save()
	{
		Matrix4f top = m_MatrixStack.top();
		m_MatrixStack.push(top);
	}

	void GLGraphics2D::setMatrix(Matrix4f matrix)
	{
		flush();
		m_MatrixStack.top() = matrix;
	}

	Matrix4f GLGraphics2D::getMatrix()
	{
		return m_MatrixStack.top();
	}

	void GLGraphics2D::translate(Vector2f translation)
	{
		flush();
		m_MatrixStack.top() = m_MatrixStack.top() * Matrix4f::translation(translation.x, translation.y, 0);
	}

	void GLGraphics2D::scale(Vector2f scale)
	{
		flush();
		m_MatrixStack.top() = m_MatrixStack.top() * Matrix4f::scaled(scale.x, scale.y, 1);
	}

	void GLGraphics2D::rotate(float amountInDegrees)
	{
		flush();
		m_MatrixStack.top() = m_MatrixStack.top() * Matrix4f::rotation(amountInDegrees, Vector3f(0,0,1));
	}

	void GLGraphics2D::clipRect(Rectanglef rectangle)
	{
	}

	void GLGraphics2D::reset()
	{
		flush();
		Vector2f size;
		
		if (m_Surface == nullptr) {
			size = Vector2f(m_Window->getWidth(), m_Window->getHeight());
		}
		else {
			size = Vector2f(m_Surface->getWidth(), m_Surface->getHeight());
		}

		m_MatrixStack.top() = Matrix4f::orthographic(0, size.width, size.height, 0, -100, 100);
	}

	void GLGraphics2D::restore()
	{
		if (m_MatrixStack.size() <= 1)
			return;
			
		flush();
		m_MatrixStack.pop();
	}

	void GLGraphics2D::drawRectangle(const Paint & paint, Rectanglef rectangle)
	{
		// In case we are not drawing yet
		m_Batch.begin();

		if (paint.getStyle() == Paint::Fill) {
			m_Batch.texture(m_WhiteTexture);

			m_Batch.color(paint.getColor());

			m_Batch.vertex(rectangle.topleft());
			m_Batch.vertex(rectangle.topright());
			m_Batch.vertex(rectangle.bottomright());
			m_Batch.vertex(rectangle.bottomleft());
		}
		else {
			drawLine(paint, rectangle.topleft(), rectangle.topright());
			drawLine(paint, rectangle.topright(), rectangle.bottomright());
			drawLine(paint, rectangle.bottomright(), rectangle.bottomleft());
			drawLine(paint, rectangle.bottomleft(), rectangle.topleft());
		}
	}
	void GLGraphics2D::drawRoundedRectangle(const Paint & paint, Rectanglef rectangle, float r)
	{
		Vector2f xo = Vector2f(r, 0);
		Vector2f yo = Vector2f(0, r);

		Rectanglef inner = Rectanglef(rectangle.position + Vector2f(r, r), rectangle.size - Vector2f(r * 2, r * 2));

		// Draw corners
		drawArc(paint, inner.topleft(), r, -PI, PI / 2);
		drawArc(paint, inner.topright(), r,-PI / 2, PI / 2);
		drawArc(paint, inner.bottomright(), r, 0, PI / 2);
		drawArc(paint, inner.bottomleft(), r, PI / 2, PI / 2);

		if (paint.getStyle() == Paint::Stroke) {
			drawLine(paint, inner.topleft() - yo, inner.topright() - yo);
			drawLine(paint, inner.topright() + xo, inner.bottomright() + xo);
			drawLine(paint, inner.bottomright() + yo, inner.bottomleft() + yo);
			drawLine(paint, inner.bottomleft() - xo, inner.topleft() - xo);
		}
		else {
			// Fill middle section
			drawRectangle(paint, Rectanglef(inner.position - yo, inner.size + yo * 2));

			// Fill the left and the right parts
			drawRectangle(paint, Rectanglef(inner.topleft() - xo, Vector2f(r, inner.height())));
			drawRectangle(paint, Rectanglef(inner.topright(), Vector2f(r, inner.height())));
		}
	}

	// Functions that just call other functions with standard arguments
	void GLGraphics2D::drawCircle(const Paint & paint, Vector2f center, float radius)
	{
		drawElipse(paint, center, radius, radius);
	}

	void GLGraphics2D::drawLine(const Paint & paint, Vector2f pos1, Vector2f pos2)
	{
		Vector2f normal = Vector2f::perp(pos2 - pos1).normalize();
		float hw = paint.getStrokeWidth() * 0.5f;

		m_Batch.begin();

		m_Batch.texture(m_WhiteTexture);

		m_Batch.color(paint.getColor());

		m_Batch.vertex(pos1 + normal * hw);
		m_Batch.vertex(pos2 + normal * hw);
		m_Batch.vertex(pos2 - normal * hw);
		m_Batch.vertex(pos1 - normal * hw);
	}

	void GLGraphics2D::drawElipse(const Paint & paint, Rectanglef rectangle)
	{
		drawElipse(paint, rectangle.center(), rectangle.width() / 2, rectangle.height() / 2);
	}

	void GLGraphics2D::drawElipse(const Paint & paint, Vector2f center, float radiusx, float radiusy)
	{
		drawArc(paint, center, radiusx, radiusy, 0, PI * 2);
	}

	void GLGraphics2D::drawArc(const Paint & paint, Vector2f center, float radius, float startAngle, float sweepAngle)
	{
		drawArc(paint, center, radius, radius, startAngle, sweepAngle);
	}

	// Actual drawing of the arc
	void GLGraphics2D::drawArc(const Paint & paint, Vector2f center, float radiusx, float radiusy, float startAngle, float sweepAngle)
	{
		// Setting up the batch
		m_Batch.begin();

		m_Batch.texture(m_WhiteTexture);
		m_Batch.color(paint.getColor());

		// Setting up the math
		int segments = (int) abs((sweepAngle / m_CirclePrecision));
		if (segments <= 0) segments = 1;

		float increment = sweepAngle / segments;

		auto calculatePos = [&](float angle) -> Vector2f {
			float s = sin(angle);
			float c = cos(angle);

			return center + Vector2f(c * radiusx, s * radiusy);
		};

		float currentAngle = startAngle;
		Vector2f previousPos = calculatePos(currentAngle);

		for (int i = 0; i < segments; i++) {
			currentAngle += increment;

			Vector2f newPos = calculatePos(currentAngle);

			if (paint.getStyle() == Paint::Fill) {
				m_Batch.vertex(center);
				m_Batch.vertex(center);
				m_Batch.vertex(previousPos);
				m_Batch.vertex(newPos);
			}
			else {
				drawLine(paint, previousPos, newPos);
			}

			previousPos = newPos;
		}
	}

	void GLGraphics2D::drawSpiral(const Paint & paint, Vector2f center, float radiusStart, float radiusEnd, float startAngle, float sweepAngle)
	{
		// Setting up the batch
		m_Batch.begin();

		m_Batch.texture(m_WhiteTexture);
		m_Batch.color(paint.getColor());

		// Setting up the math
		int segments = (int)abs((sweepAngle / m_CirclePrecision)); 
		if (segments <= 0) segments = 1;

		float angleIncrement = sweepAngle / segments;
		float radiusIncrement = (radiusEnd - radiusStart) / segments;

		auto calculatePos = [&](float angle, float radius) -> Vector2f {
			float s = sin(angle);
			float c = cos(angle);

			return center + Vector2f(c * radius, s * radius);
		};

		float currentAngle = startAngle;
		float currentRadius = radiusStart;
		Vector2f previousPos = calculatePos(currentAngle, currentRadius);

		for (int i = 0; i < segments; i++) {
			currentAngle += angleIncrement;
			currentRadius += radiusIncrement;

			Vector2f newPos = calculatePos(currentAngle, currentRadius);

			m_Batch.vertex(center);
			m_Batch.vertex(center);
			m_Batch.vertex(previousPos);
			m_Batch.vertex(newPos);

			previousPos = newPos;
		}
	}

	void GLGraphics2D::drawText(const Paint & paint, Vector2f pos, const std::string &text, Vector2f scale)
	{
		auto font = paint.getFont();

		if (font == nullptr)
			return;

		float xoffset = 0;
		float yoffset = 0;

		// TODO per line centering

		{
			auto rect = font->measureText(text);

			if (paint.getHorizontalAlignment() == Paint::HAlign::Center) {
				xoffset = -rect.size.x * 0.5f;
			}
			if (paint.getHorizontalAlignment() == Paint::HAlign::Right) {
				xoffset = -rect.size.x * scale.x;
			}


			if (paint.getVerticalAlignment() == Paint::VAlign::Center) {
				yoffset = -rect.size.y * 0.5f;
			}
			if (paint.getVerticalAlignment() == Paint::VAlign::Bottom) {
				yoffset = -rect.size.y;
			}
		}

		float xStart = xoffset;

		for (int i = 0; i < text.size(); i++) {
			char c = text[i];

			if (c == '\n') {
				xoffset = xStart;
				yoffset += font->getHeight() + 1; // TODO nice font spacing
				continue;
			}
			if (c == ' ') {
				xoffset += 3; // TODO nice spacebar handling
				continue;
			}

			auto &r = font->getCharacter(c);

			if (!r)
				continue;

			auto &fc = *r;

			drawSprite(paint, fc.sprite, pos + Vector2f(xoffset + fc.xoffset, yoffset + fc.yoffset) * scale, scale);

			xoffset += fc.xadvance;
		}
	}

	void GLGraphics2D::drawSprite(const Paint & paint, const Sprite &sprite, Vector2f pos)
	{
		drawSprite(paint, sprite, pos, Vector2f(1, 1), 0);
	}

	void GLGraphics2D::drawSprite(const Paint & paint, const Sprite & sprite, Vector2f pos, Vector2f scale)
	{
		drawSprite(paint, sprite, pos, scale, 0);
	}

	void GLGraphics2D::drawSprite(const Paint & paint, const Sprite &sprite, Vector2f pos, Vector2f scale, float angle)
	{
		// In case we are not drawing yet
		m_Batch.begin();

		auto texture = std::dynamic_pointer_cast<GLTexture>(sprite.getTexture());
		auto surface = std::dynamic_pointer_cast<GLSurface>(sprite.getTexture());

		if (texture != nullptr) {
			m_Batch.texture(texture);
		}
		if (surface != nullptr) {
			m_Batch.texture(surface->getGLTexture());
		}

		Rectanglef uvs = sprite.getUVRectangle();
		Rectanglef rect = Rectanglef(-sprite.getOrigin(), sprite.getSize());

		Matrix3f matrix = Matrix3f::identity().translate(pos.x, pos.y).rotate(angle).scale(scale.x, scale.y);

		m_Batch.color(paint.getColor());

		m_Batch.uv(uvs.topleft());
		m_Batch.vertex(matrix * rect.topleft());

		m_Batch.uv(uvs.topright());
		m_Batch.vertex(matrix * rect.topright());

		m_Batch.uv(uvs.bottomright());
		m_Batch.vertex(matrix * rect.bottomright());

		m_Batch.uv(uvs.bottomleft());
		m_Batch.vertex(matrix * rect.bottomleft());
	}

	void GLGraphics2D::drawSurface(const Paint & paint, const Surface & surface, Vector2f pos)
	{
		drawSurface(paint, surface, pos, Vector2f(1, 1), 0);
	}

	void GLGraphics2D::drawSurface(const Paint & paint, const Surface & surface, Vector2f pos, Vector2f scale)
	{
		drawSurface(paint, surface, pos, scale, 0);
	}

	void GLGraphics2D::drawSurface(const Paint & paint, const Surface & surface, Vector2f pos, Vector2f scale, float angle)
	{// In case we are not drawing yet
		m_Batch.begin();

		// Ugly
		auto texture = (GLSurface*)(&surface);

		m_Batch.texture(texture->getGLTexture());

		Rectanglef uvs = Rectanglef(0, 0, 1, 1);
		Rectanglef rect = Rectanglef(0, 0, (float) surface.getWidth(), (float) surface.getHeight());

		Matrix3f matrix = Matrix3f::identity().translate(pos.x, pos.y).rotate(angle).scale(scale.x, scale.y);

		m_Batch.color(paint.getColor());

		m_Batch.uv(uvs.topleft());
		m_Batch.vertex(matrix * rect.topleft());

		m_Batch.uv(uvs.topright());
		m_Batch.vertex(matrix * rect.topright());

		m_Batch.uv(uvs.bottomright());
		m_Batch.vertex(matrix * rect.bottomright());

		m_Batch.uv(uvs.bottomleft());
		m_Batch.vertex(matrix * rect.bottomleft());
	}

	void GLGraphics2D::drawClear(Color32 color)
	{
		//TODO discard, instead of flush.
		flush();

		glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLGraphics2D::drawClearDepth()
	{
		//TODO discard, instead of flush.
		flush();
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	float GLGraphics2D::getWidth()
	{
		assert(m_Surface != nullptr || m_Window != nullptr);

		if (m_Surface == nullptr) {
			return m_Window->getWidth();
		}
		else {
			return m_Surface->getWidth();
		}
	}
	float GLGraphics2D::getHeight()
	{
		assert(m_Surface != nullptr || m_Window != nullptr);

		if (m_Surface == nullptr) {
			return m_Window->getHeight();
		}
		else {
			return m_Surface->getHeight();
		}
	}

	void GLGraphics2D::flush()
	{
		assert(m_Surface != nullptr || m_Window != nullptr);

		//Not sure if i should do this here but whatever
		if (m_Surface == nullptr) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, m_Window->getRawWidth(), m_Window->getRawHeight());
		}
		else {
			m_Surface->bind();
			glViewport(0, 0, m_Surface->getWidth(), m_Surface->getHeight());
		}

		m_Batch.setMatrixView(m_MatrixStack.top());
		
		m_Batch.end();
	}
}
