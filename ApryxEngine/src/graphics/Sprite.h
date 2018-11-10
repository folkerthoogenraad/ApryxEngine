#pragma once

#include <memory>

#include "Texture.h"

#include "math/Rectangle.h"
#include "math/Vector2.h"

namespace apryx {

	class Sprite {
		Rectanglef m_TextureRectangle;

		Vector2f m_Origin;
		Vector2f m_Size;

		std::shared_ptr<Texture> m_Texture;
	public:
		Sprite(std::shared_ptr<Texture> texture = nullptr);
		Sprite(std::shared_ptr<Texture> texture, float x, float y, float width, float height);

		Rectanglef getUVRectangle() const { return m_TextureRectangle; }

		Vector2f getOrigin() const { return m_Origin; }
		Vector2f getSize() const { return m_Size; }

		Sprite &setSize(Vector2f size) { m_Size = size; return *this; }
		Sprite &setOrigin(Vector2f origin) { m_Origin = origin; return *this; }

		Sprite &setCenter();

		const std::shared_ptr<Texture> &getTexture() const { return m_Texture; }

		// Only use with care
		void setTextureRectangle(Rectanglef rectangle) { m_TextureRectangle = rectangle; }
	};

}