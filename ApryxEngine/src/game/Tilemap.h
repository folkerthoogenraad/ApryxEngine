#pragma once

#include <vector>

#include "graphics/Sprite.h"
#include "graphics/Graphics2D.h"

namespace apryx {

	class Tilemap {
		int m_Width;
		int m_Height;

		float m_TileHeight;
		float m_TileWidth;

		std::vector<int> m_Colliders;
		std::vector<std::optional<Sprite>> m_Sprites;
	public:
		Tilemap(int w, int h, float tileWidth, float tileHeight);

		void draw(Graphics2D &graphics);

		inline void setTileCollider(int x, int y, int index) { m_Colliders[x + y * m_Width] = index; }
		inline void setTileSprite(int x, int y, Sprite sprite) { m_Sprites[x + y * m_Width] = sprite; }

		inline int getTileCollider(int x, int y) const { return m_Colliders[x + y * m_Width]; }
		inline std::optional<Sprite> getTileSprite(int x, int y) const { return m_Sprites[x + y * m_Width]; }
	};

}