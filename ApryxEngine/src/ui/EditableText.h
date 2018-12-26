#pragma once

#include <string>

namespace apryx{

	struct Carret {
		// The selection in text
		int start = 0;
		int end = 0;

		// NOTE the start does not have to be before the end. 
	};
	
	class EditableText {
		std::string m_Text;
		Carret m_Carret;
	public:
		enum CarretPosition {
			Begin,
			End
		};
	public:
		// TODO some consistancy in the naming
		void insert(char c);

		void del(bool word);
		void backspace(bool word);

		void moveTo(int pos, bool hold);
		void moveTo(CarretPosition pos, bool hold);
		void move(int direction, bool hold, bool word);

		void setCarretPosition(int pos, bool startOnly = false);
		void setCarretPosition(CarretPosition position);

		void removeSelectedCharacters();

		int getSelectionSize() const;

		const std::string &getText() const { return m_Text;}
		void setText(std::string text);

		int getNextSpace(int from, int direction) const;

		int length() const;
		const Carret &getCarret() const { return m_Carret; }

		void clampCarret();
	};

}