#include "Font.h"

namespace apryx {
	const std::optional<FontCharacter>& Font::getCharacter(char c)
	{
		return m_Characters[c];
	}

	void Font::setCharacter(char index, FontCharacter sprite)
	{
		m_Characters[index] = sprite;
	}

	FontBuilder::FontBuilder(std::shared_ptr<Texture> texture)
		:m_Font(std::make_shared<Font>()), x(0), y(0), m_Texture(texture)
	{
	}

	void FontBuilder::addChar(char c, float w, float h, float xadvance, float xoffset, float yoffset, float next)
	{
		FontCharacter fc;
		fc.xadvance = xadvance;
		fc.xoffset = xoffset;
		fc.yoffset = yoffset;
		fc.sprite = Sprite(m_Texture, x, y, w, h);

		m_Font->setCharacter(c, fc);

		nextChar(next);
	}

}