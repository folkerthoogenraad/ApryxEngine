#include "GLGraphics2D.h"

#include "graphics/Image.h"
#include "opengl/GL.h"

#include "math/Matrix3.h"


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
	void GLGraphics2D::drawElipse(Paint & paint, Rectanglef rectangle)
	{
	}
	void GLGraphics2D::drawRoundedRectangle(Paint & paint, Rectanglef rectangle, Rounding rounding)
	{
	}
	void GLGraphics2D::drawArc(Paint & paint, Vector2f center, float radius, float startAngle, float sweepAngle)
	{
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
