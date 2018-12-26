#include "Button.h"

#include "math/math.h"

#include <iostream>

namespace apryx {
	Button::Button(std::string text, ButtonType type)
		: m_EditableText(text), m_Type(type)
	{ }

	void Button::init(ApryxUI *ui)
	{
		UIComponent::init(ui);

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

		if (m_Pressed) {
			backgroundPaint.setColor(style.primaryPressed);
		}

		Paint textPaint;
		textPaint.setFont(m_Font);
		textPaint.setVerticalAlignment(Paint::VAlign::Center);
		textPaint.setHorizontalAlignment(Paint::HAlign::Center);

		if (m_Type == ButtonType::Primary) {
			textPaint.setColor(style.contrast);
		}
		if (m_Type == ButtonType::Secondary) {
			textPaint.setColor(backgroundPaint.getColor());
			backgroundPaint.setStyle(Paint::Stroke);
		}

		float rounding = min_t(bounds.height() / 2.0f, 20.0f);

		graphics.drawRoundedRectangle(backgroundPaint, bounds, rounding);
		graphics.drawText(textPaint, bounds.center(), m_EditableText);
	}

	Size Button::getPreferredSize() const
	{
		Size size = Size(128, 40);

		Rectanglef boundingBox = m_Font->measureText(m_EditableText);

		size.width = max_t(boundingBox.width() + 40, size.width);
		size.height = max_t(boundingBox.height() + 24, size.height);

		return size;
	}

	void Button::onMousePressed(InputEvent event)
	{
		m_Pressed = true;
		redraw();
	}
	void Button::onMouseReleased(InputEvent event)
	{
		m_Pressed = false;
		redraw();
	}

	void Button::onMouseClick(InputEvent event)
	{

	}
}
