#include "Font.h"

#include "math/math.h"

namespace apryx {
	const std::optional<FontCharacter>& Font::getCharacter(char c) const
	{
		return m_Characters[c];
	}

	Rectanglef Font::measureText(const std::string & text) const
	{
		float xoffset = 0;
		float yoffset = getHeight();

		Rectanglef rect(0,0,0,0);

		for (int i = 0; i < text.size(); i++) {
			char c = text[i];

			if (c == '\n') {
				xoffset = 0;
				yoffset += getHeight(); // TODO nice font spacing
				continue;
			}
			if (c == ' ') {
				xoffset += 3; // TODO nice spacebar handling
				continue;
			}

			auto &r = getCharacter(c);

			if (!r)
				continue;

			auto &fc = *r;

			xoffset += fc.xadvance;

			rect.size.x = max_t(xoffset, rect.size.x);
			rect.size.y = max_t(yoffset, rect.size.y);
		}

		return rect;
	}

	void Font::setCharacter(char index, FontCharacter sprite)
	{
		m_Characters[index] = sprite;
	}

	void Font::scale(float scaleFactor)
	{
		m_Height *= scaleFactor;

		for (auto c : m_Characters) {
			if (c) {
				c->sprite.setSize(c->sprite.getSize() * scaleFactor);
				c->sprite.setOrigin(c->sprite.getOrigin() * scaleFactor);
			}
		}
	}

	FontBuilder::FontBuilder(std::shared_ptr<Texture> texture)
		:m_ButtonFont(std::make_shared<Font>()), x(0), y(0), m_Texture(texture)
	{
	}

	void FontBuilder::addChar(char c, float w, float h, float xadvance, float xoffset, float yoffset, float next)
	{
		FontCharacter fc;
		fc.xadvance = xadvance;
		fc.xoffset = xoffset;
		fc.yoffset = yoffset;
		fc.sprite = Sprite(m_Texture, x, y, w, h);

		m_ButtonFont->setCharacter(c, fc);

		nextChar(next);
	}

}