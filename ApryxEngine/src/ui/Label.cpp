#include "Label.h"

namespace apryx {
	Label::Label(std::string text)
		: m_EditableText(text)
	{ }

	void Label::init(ApryxUI * ui)
	{
		UIComponent::init(ui);

		if (m_Font == nullptr)
			m_Font = ui->getStyle().textFont;
	}

	void Label::draw(Graphics2D & graphics)
	{
		auto bounds = getLocalBounds();

		auto &style = getUI()->getStyle();

		Paint paint;
		paint.setColor(style.foreground);
		paint.setHorizontalAlignment(Paint::HAlign::Center);
		paint.setVerticalAlignment(Paint::VAlign::Center);
		paint.setFont(m_Font);

		graphics.drawText(paint, bounds.center(), m_EditableText);
	}


	Size apryx::Label::getPreferredSize() const
	{
		Rectanglef boundingBox = m_Font->measureText(m_EditableText);
		return boundingBox.size;
	}
}
