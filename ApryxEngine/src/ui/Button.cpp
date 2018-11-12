#include "Button.h"

namespace apryx {
	Button::Button(std::string text)
		: m_Text(text)
	{ }

	void Button::init()
	{
		ApryxUIStyle &style = getUI()->getStyle();

		if (m_Font == nullptr)
			m_Font = style.componentFont;
	}

	void Button::draw(Graphics2D & graphics)
	{
		Rectanglef bounds = getLocalBounds();
		ApryxUIStyle &style = getUI()->getStyle();

		Paint backgroundPaint;
		backgroundPaint.setColor(style.primary);

		Paint textPaint;
		textPaint.setFont(m_Font);
		textPaint.setVerticalAlignment(Paint::VAlign::Center);
		textPaint.setHorizontalAlignment(Paint::HAlign::Center);

		if (m_Type == ButtonType::Primary) {
			textPaint.setColor(style.contrast);
		}
		if (m_Type == ButtonType::Secondary) {
			textPaint.setColor(style.primary);
			backgroundPaint.setStyle(Paint::Stroke);
		}

		graphics.drawRoundedRectangle(backgroundPaint, bounds, bounds.height() / 2);
		graphics.drawText(textPaint, bounds.center(), m_Text);
	}
}
