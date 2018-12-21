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
		const std::optional<FontCharacter> &getCharacter(char c) const;

		float getHeight() const { return m_Height; }

		Rectanglef measureText(const std::string &text) const;

		// Only use if you know what you are doing. So just dont actually.
		void setHeight(float height) { m_Height = height; }
		void setCharacter(char index, FontCharacter character);

		void scale(float scaleFactor);
	};

	class FontBuilder {
		std::shared_ptr<Font> m_ButtonFont;

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

		std::shared_ptr<Font> getFont() { return m_ButtonFont; };
	};
}