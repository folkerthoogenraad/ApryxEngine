#include "InputManager.h"

#include "console/Console.h"

namespace apryx {
	bool InputManager::isKeyDown(int key)
	{
		return m_DownKeys.find(key) != m_DownKeys.end();
	}
	bool InputManager::isKeyUp(int key)
	{
		return m_ButtonsReleased.find(key) != m_ButtonsReleased.end();
	}
	bool InputManager::isKeyPressed(int key)
	{
		return m_ButtonsPressed.find(key) != m_ButtonsPressed.end();
	}

	const Gamepad & InputManager::getGamepad(int index) const
	{
		return m_Gamepads[index];
	}

	void InputManager::clear() {
		m_ButtonsReleased.clear();
		m_ButtonsPressed.clear();
	}

	void InputManager::processEvents(const std::vector<InputEvent>& inputs)
	{
		for (auto &event : inputs) {
			switch (event.m_EventType)
			{
			case InputEvent::KeyboardPressed:
				m_ButtonsPressed.insert(event.m_KeyCode);
				m_DownKeys.insert(event.m_KeyCode);
				break;

			case InputEvent::KeyboardReleased:
				m_ButtonsReleased.insert(event.m_KeyCode);
				m_DownKeys.erase(event.m_KeyCode); 
				break;
			}
		}

		int index = 0;
		for (auto &g : m_Gamepads) {
			g.processEvents(inputs, index++);
		}
	}
}
