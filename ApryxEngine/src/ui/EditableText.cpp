#include "EditableText.h"

#include <assert.h>

namespace apryx {

	void EditableText::insert(char c)
	{
		removeSelectedCharacters();

		m_Text.insert(m_Carret.start, 1, c);
		
		m_Carret.start++;
		m_Carret.end++;
	}

	void EditableText::del(bool word)
	{
		if (getSelectionSize() != 0) {
			removeSelectedCharacters();
			return;
		}

		if (m_Carret.start >= length())
			return;

		int count = 1;

		if (word) {
			int end = getNextSpace(m_Carret.start, 1);

			count = end - m_Carret.start;

			assert(m_Carret.start + count <= length());
		}

		m_Text.erase(m_Carret.start, count);

		m_Carret.end = m_Carret.start;
	}

	void EditableText::backspace(bool word)
	{
		if (getSelectionSize() != 0){
			removeSelectedCharacters();
			return;
		}

		if (m_Carret.start <= 0)
			return;

		int count = 1;

		if (word) {
			int end = getNextSpace(m_Carret.start, -1);

			count = m_Carret.start - end;

			assert(m_Carret.start - count >= 0);
		}

		m_Text.erase(m_Carret.start - count, count);

		m_Carret.start -= count;
		m_Carret.end -= count;
	}

	void EditableText::moveTo(int pos, bool hold)
	{
		m_Carret.start = pos;

		if (!hold) {
			m_Carret.end = m_Carret.start;
		}

		clampCarret();
	}

	void EditableText::moveTo(CarretPosition pos, bool hold)
	{
		switch (pos)
		{
		case CarretPosition::Begin:
			moveTo(0, hold);
			break;
		case CarretPosition::End:
			moveTo(length() - 1, hold);
			break;

		default: // Set end
			moveTo(length() - 1, hold);
		}
	}

	void EditableText::move(int direction, bool hold, bool word)
	{
		int newPos = m_Carret.start + direction;

		if (word) {
			newPos = getNextSpace(m_Carret.start, direction);
		}

		m_Carret.start = newPos;

		if (!hold) {
			m_Carret.end = m_Carret.start;
		}

		clampCarret();
	}

	void EditableText::setCarretPosition(int pos, bool start)
	{
		if (pos < 0) pos = 0;
		if (pos > length()) pos = length();

		m_Carret.start = pos;

		if(!start)
			m_Carret.end = pos;
	}

	void EditableText::setCarretPosition(CarretPosition position)
	{
		switch (position)
		{
		case CarretPosition::Begin:
			setCarretPosition(0);
			break;
		case CarretPosition::End:
			setCarretPosition(length() - 1);
			break;

		default: // Set end
			setCarretPosition(length() - 1);
		}
	}

	void EditableText::removeSelectedCharacters()
	{
		if (getSelectionSize() == 0)
			return;
		
		int from = m_Carret.start;
		int to = m_Carret.end;

		if (from > to)
			std::swap(from, to);
		
		m_Text.erase(from, to - from);

		m_Carret.start = from;
		m_Carret.end = from;
	}

	int EditableText::getSelectionSize() const
	{
		return m_Carret.end - m_Carret.start;
	}

	void EditableText::setText(std::string text)
	{
		m_Text = std::move(text);

		setCarretPosition(CarretPosition::End);
	}

	int EditableText::getNextSpace(int from, int dir) const
	{
		if (from < 0)
			from = 0;
		
		if (from > length())
			from = length();

		assert(dir == -1 || dir == 1);

		int pos = from;

		if (dir < 0) {
			pos -= 1;
		}

		// Clear whitespace first
		while (pos >= 0 && pos < length() && m_Text[pos] == ' ') {
			pos += dir;
		}

		// Search for not whitespace
		while (pos >= 0 && pos < length() && m_Text[pos] != ' ') {
			pos += dir;
		}

		if (pos < 0) pos = 0;
		if (pos > length()) pos = length();

		return pos;
	}

	int EditableText::length() const
	{
		return (int)m_Text.size();
	}

	void EditableText::clampCarret()
	{
		if (m_Carret.start < 0) m_Carret.start = 0;
		if (m_Carret.start > length()) m_Carret.start = length();

		if (m_Carret.end < 0) m_Carret.end = 0;
		if (m_Carret.end > length()) m_Carret.end = length();
	}
}
