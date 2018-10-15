#pragma once

#include "resources/ResourceManager.h"

namespace apryx {

	class Win32ResourceManager : public ResourceManager{
		std::shared_ptr<Window> m_Window;
	public:
		Win32ResourceManager(std::shared_ptr<Window> window);

		virtual std::shared_ptr<Window> getWindow() { return m_Window; }
	};

}