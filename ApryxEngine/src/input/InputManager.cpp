#include "InputManager.h"

#include "log/Log.h"

namespace apryx {
	bool InputManager::isKeyDown(int key)
	{
		return m_DownKeys.find(key) != m_DownKeys.end();
	}
	bool InputManager::isKeyUp(int key)
	{
		return m_UpKeys.find(key) != m_UpKeys.end();
	}
	bool InputManager::isKeyPressed(int key)
	{
		return m_PressedKeys.find(key) != m_PressedKeys.end();
	}

	void InputManager::clear() {
		m_UpKeys.clear();
		m_PressedKeys.clear();
	}

	void InputManager::processEvents(const std::vector<InputEvent>& inputs)
	{
		for (auto &event : inputs) {
			switch (event.m_EventType)
			{
			case InputEvent::KeyboardPressed:
				m_PressedKeys.insert(event.m_KeyCode);
				m_DownKeys.insert(event.m_KeyCode);
				break;

			case InputEvent::KeyboardReleased:
				m_UpKeys.insert(event.m_KeyCode);
				m_DownKeys.erase(event.m_KeyCode); 
				break;
			}
		}
	}
}
