#pragma once

#include "Sprite.h"
#include "Texture.h"

#include <optional>
#include <array>

namespace apryx {

	class FontCharacter {
	public:
		Sprite sprite;

		float xadvance;

		float xoffset;
		float yoffset;
	};

	class Font{
		std::array<std::optional<FontCharacter>, 255> m_Characters;

		float m_Height = 5;
	public:
		const std::optional<FontCharacter> &getCharacter(char c);
		void setCharacter(char index, FontCharacter character);

		float getHeight() const { return m_Height; }
	};

	class FontBuilder {
		std::shared_ptr<Font> m_Font;

		std::shared_ptr<Texture> m_Texture;

		float x, y;

		float height;
		float lineSpacing;
	public:
		FontBuilder(std::shared_ptr<Texture> texture);

		void setLineSpacing(float spacing) { lineSpacing = spacing; }
		void setHeight(float height) { this->height = height; }
		void setPosition(float x, float y) { this->x = x; this->y = y; }

		void newLine() { y += height + lineSpacing; x = 0; }
		void nextChar(float w) { x += w; }

		void addChar(char c, float w, float h, float xadvance, float xoffset, float yoffset, float nextChar);

		std::shared_ptr<Font> getFont() { return m_Font; };
	};
}