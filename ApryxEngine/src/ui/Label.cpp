#include "Label.h"

namespace apryx {
	Label::Label(std::string text)
		: m_Text(text)
	{ }

	void Label::init(ApryxUI * ui)
	{
		if (m_Font == nullptr)
			m_Font = ui->getStyle().textFont;
	}

	void Label::draw(Graphics2D & graphics)
	{
		auto bounds = getLocalBounds();

		Paint paint;
		paint.setColor(Color32::black());
		paint.setHorizontalAlignment(Paint::HAlign::Center);
		paint.setVerticalAlignment(Paint::VAlign::Center);
		paint.setFont(m_Font);

		graphics.drawText(paint, bounds.center(), m_Text);
	}


	Size apryx::Label::getPreferredSize() const
	{
		Rectanglef boundingBox = m_Font->measureText(m_Text);
		return boundingBox.size;
	}
}
