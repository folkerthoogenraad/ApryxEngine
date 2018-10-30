#pragma once

#include "InputEvent.h"

#include <vector>
#include <set>

namespace apryx {

	class InputManager {
		std::set<int> m_DownKeys;
		std::set<int> m_UpKeys;
		std::set<int> m_PressedKeys;

		std::string m_TypedString;
	public:
		bool isKeyDown(int key);
		bool isKeyUp(int key);
		bool isKeyPressed(int key);

		const std::string &getTypedString() const { return m_TypedString; }

		void clear();
		void processEvents(const std::vector<InputEvent> &inputs);
	};

}