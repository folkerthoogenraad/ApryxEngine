#include "TextField.h"
#include <iostream>

namespace apryx {
	TextField::TextField(std::string hint)
		:m_Hint(hint)
	{

	}

	void TextField::init(ApryxUI *ui)
	{
		UIComponent::init(ui);

		if (m_Font == nullptr)
		{
			m_Font = ui->getStyle().textFont;
		}
	}
	
	void TextField::draw(Graphics2D & graphics)
	{
		auto bounds = getLocalBounds();
		auto style = getUI()->getStyle();

		Paint carretPaint;
		carretPaint.setColor(style.foreground);

		Paint selectionPaint;
		selectionPaint.setColor(style.selection);

		Paint textPaint;
		textPaint.setColor(style.foreground);
		textPaint.setFont(m_Font);
		textPaint.setVerticalAlignment(Paint::VAlign::Center);

		Paint linePaint;
		linePaint.setColor(style.inactive);
		linePaint.setStrokeWidth(2);

		if (m_Focussed) {
			linePaint.setColor(style.primary);
		}

		if (m_EditableText.length() == 0 && !m_Focussed) {
			textPaint.setColor(style.inactive);
		}

		Vector2f textPosition = bounds.topleft() + Vector2f(0, bounds.height() * 0.5f);

		if(m_EditableText.length() == 0 && !m_Focussed)
			graphics.drawText(textPaint, textPosition, m_Hint);
		else
			graphics.drawText(textPaint, textPosition, m_EditableText.getText());

		if (m_Focussed) {
			int pos = m_EditableText.getCarret().start;

			Vector2f offset = m_Font->getOffsetByIndex(m_EditableText.getText(), pos);

			// Translate that to the right position 
			// TODO with multiline this breaks.
			offset += bounds.topleft() + Vector2f(0, bounds.height() * 0.5f - m_Font->getHeight() / 2);

			graphics.drawLine(carretPaint, offset, offset + Vector2f(0, m_Font->getHeight()));
		}

		if (m_Focussed && m_EditableText.getSelectionSize() != 0) {
			Vector2f start = m_Font->getOffsetByIndex(m_EditableText.getText(), m_EditableText.getCarret().start);
			Vector2f end = m_Font->getOffsetByIndex(m_EditableText.getText(), m_EditableText.getCarret().end);

			start += bounds.topleft() + Vector2f(0, bounds.height() * 0.5f - m_Font->getHeight() / 2);
			end += bounds.topleft() + Vector2f(0, bounds.height() * 0.5f - m_Font->getHeight() / 2);

			if (start.x > end.x)
				std::swap(start, end);

			Rectanglef rect = Rectanglef(start.x, start.y, end.x - start.x, m_Font->getHeight());
			graphics.drawRectangle(selectionPaint, rect);
		}

		graphics.drawLine(linePaint, bounds.bottomright(), bounds.bottomleft());
	}

	Size TextField::getPreferredSize() const
	{
		// TODO make actual size pls
		return Size(128, 32);
	}

	void TextField::onKeyPressed(InputEvent event) 
	{
		if (event.getKeyCode() == KEY_BACKSPACE) {
			m_EditableText.backspace(event.isCrtlDown());
			redraw();
		}
		if (event.getKeyCode() == KEY_DELETE) {
			m_EditableText.del(event.isCrtlDown());
			redraw();
		}
		if (event.getKeyCode() == KEY_LEFT) {
			m_EditableText.move(-1, event.isShiftDown(), event.isCrtlDown());
			redraw();
		}
		if (event.getKeyCode() == KEY_RIGHT) {
			m_EditableText.move(1, event.isShiftDown(), event.isCrtlDown());
			redraw();
		}

		if (event.getKeyCode() == KEY_HOME) {
			m_EditableText.moveTo(EditableText::Begin, event.isShiftDown());
			redraw();
		}
		if (event.getKeyCode() == KEY_END) {
			m_EditableText.moveTo(EditableText::End, event.isShiftDown());
			redraw();
		}
	}

	void TextField::onMousePressed(InputEvent event)
	{
		m_EditableText.setCarretPosition(positionToIndex(
			event.getMousePosition())
		);

		redraw();
	}

	void TextField::onMouseDrag(InputEvent event)
	{
		m_EditableText.setCarretPosition(positionToIndex(
			event.getMousePosition()), true
		);

		redraw();
	}

	void TextField::onMouseReleased(InputEvent event)
	{
		m_EditableText.setCarretPosition(positionToIndex(
			event.getMousePosition()), true
		);

		redraw();
	}

	void TextField::onKeyTyped(InputEvent event)
	{
		char c = (char)event.getUnicodeKey();

		if (c >= 32 && c <= 126) {
			m_EditableText.insert(c);
		}

		redraw();
	}
	void TextField::onFocusGain(InputEvent event)
	{
		m_Focussed = true;
		redraw();
	}
	void TextField::onFocusLose(InputEvent event)
	{
		m_Focussed = false;
		redraw();
	}

	int TextField::positionToIndex(Vector2f position)
	{
		auto bounds = getLocalBounds();

		position -= bounds.topleft() + Vector2f(0, bounds.height() * 0.5f - m_Font->getHeight() / 2);

		return m_Font->getIndexByOffset(m_EditableText.getText(), position);
	}
}
