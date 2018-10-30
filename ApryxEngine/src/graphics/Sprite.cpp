#include "Sprite.h"

namespace apryx {
	Sprite::Sprite(std::shared_ptr<Texture> texture)
		: m_Texture(texture)
	{ 
		if (texture != nullptr)
		{
			m_TextureRectangle.position = Vector2f(0, 0);
			m_TextureRectangle.size = Vector2f(1, 1);

			m_Size = texture->getSize();
		}
	}

	Sprite::Sprite(std::shared_ptr<Texture> texture, float x, float y, float width, float height)
		: m_Texture(texture)
	{
		if (texture != nullptr && texture->getWidth() > 0 && texture->getHeight() > 0)
		{
			m_TextureRectangle = Rectanglef(
				Vector2f(x, y) / texture->getSize(),
				Vector2f(width, height) / texture->getSize());

			m_Size = Vector2f(width, height);
		}

	}

	void Sprite::setCenter()
	{
		m_Origin = m_Size / 2;
	}
}

