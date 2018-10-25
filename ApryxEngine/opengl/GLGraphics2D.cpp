#include "GLGraphics2D.h"

#include "graphics/Image.h"
#include "opengl/GL.h"

#include "math/Matrix3.h"
#include "math/math.h"


namespace apryx {

	GLGraphics2D::GLGraphics2D()
	{
		Image image = Image::colored(1, 1);
		
		m_WhiteTexture = std::make_shared<GLTexture>();
		m_WhiteTexture->setData(image);

		m_Batch.texture(m_WhiteTexture);
	}

	void GLGraphics2D::setSize(float width, float height)
	{
		m_Batch.setSize(width, height);
	}

	void GLGraphics2D::drawRectangle(Paint & paint, Rectanglef rectangle)
	{
		// In case we are not drawing yet
		m_Batch.begin();

		m_Batch.texture(m_WhiteTexture);

		m_Batch.color(paint.getColor());

		m_Batch.vertex(rectangle.topleft());
		m_Batch.vertex(rectangle.topright());
		m_Batch.vertex(rectangle.bottomright());
		m_Batch.vertex(rectangle.bottomleft());
	}
	void GLGraphics2D::drawRoundedRectangle(Paint & paint, Rectanglef rectangle, Rounding rounding)
	{
	}

	// Functions that just call other functions with standard arguments
	void GLGraphics2D::drawCircle(Paint & paint, Vector2f center, float radius)
	{
		drawElipse(paint, center, radius, radius);
	}
	void GLGraphics2D::drawElipse(Paint & paint, Rectanglef rectangle)
	{
		drawElipse(paint, rectangle.center(), rectangle.width() / 2, rectangle.height() / 2);
	}
	void GLGraphics2D::drawElipse(Paint & paint, Vector2f center, float radiusx, float radiusy)
	{
		drawArc(paint, center, radiusx, radiusy, 0, PI * 2);
	}
	void GLGraphics2D::drawArc(Paint & paint, Vector2f center, float radius, float startAngle, float sweepAngle)
	{
		drawArc(paint, center, radius, radius, startAngle, sweepAngle);
	}

	// Actual drawing of the arc
	void GLGraphics2D::drawArc(Paint & paint, Vector2f center, float radiusx, float radiusy, float startAngle, float sweepAngle)
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

			m_Batch.vertex(center);
			m_Batch.vertex(center);
			m_Batch.vertex(previousPos);
			m_Batch.vertex(newPos);

			previousPos = newPos;
		}
	}

	void GLGraphics2D::drawSpiral(Paint & paint, Vector2f center, float radiusStart, float radiusEnd, float startAngle, float sweepAngle)
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

	void GLGraphics2D::drawText(Paint & paint, Vector2f pos, std::string text)
	{
	}

	void GLGraphics2D::drawSprite(Paint & paint, Sprite &sprite, Vector2f pos)
	{
		drawSprite(paint, sprite, pos, Vector2f(1, 1), 0);
	}

	void GLGraphics2D::drawSprite(Paint & paint, Sprite & sprite, Vector2f pos, Vector2f scale)
	{
		drawSprite(paint, sprite, pos, scale, 0);
	}

	void GLGraphics2D::drawSprite(Paint & paint, Sprite &sprite, Vector2f pos, Vector2f scale, float angle)
	{
		// In case we are not drawing yet
		m_Batch.begin();

		m_Batch.texture(std::static_pointer_cast<GLTexture>(sprite.getTexture()));

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

	void GLGraphics2D::drawClear()
	{
		//TODO discard, instead of flush.
		flush();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLGraphics2D::flush()
	{
		m_Batch.end();
	}
}
