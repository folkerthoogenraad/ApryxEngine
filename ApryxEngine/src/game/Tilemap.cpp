#include "Tilemap.h"

namespace apryx {
	Tilemap::Tilemap(int w, int h, float tileWidth, float tileHeight)
		:m_Width(w), m_Height(h), m_TileWidth(tileWidth), m_TileHeight(tileHeight)
	{
		m_Colliders.resize(m_Width * m_Height);
		m_Sprites.resize(m_Width * m_Height);
	}

	void Tilemap::draw(Graphics2D & graphics)
	{
		for (int i = 0; i < m_Width; i++) {
			for (int j = 0; j < m_Height; j++) {
				auto sprite = getTileSprite(i, j);
				if (!sprite)
					continue;

				graphics.drawSprite(Paint(Color32::white()), *sprite, Vector2f(i * m_TileWidth, j * m_TileHeight));
			}
		}
	}

}
