#pragma once

#include <vector>
#include <set>
#include <array>

#include "InputEvent.h"
#include "Gamepad.h"

namespace apryx {

	class InputManager {
		std::set<int> m_DownKeys;
		std::set<int> m_ButtonsReleased;
		std::set<int> m_ButtonsPressed;

		std::array<Gamepad, 4> m_Gamepads;

		std::string m_TypedString;
	public:
		bool isKeyDown(int key);
		bool isKeyUp(int key);
		bool isKeyPressed(int key);

		const std::string &getTypedString() const { return m_TypedString; }

		const Gamepad &getGamepad(int index) const;

		void clear();
		void processEvents(const std::vector<InputEvent> &inputs);
	};

}