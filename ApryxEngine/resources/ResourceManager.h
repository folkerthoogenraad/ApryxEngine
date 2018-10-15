#pragma once

#include <memory>

#include "graphics/Window.h"

namespace apryx {

	class ResourceManager {
	public:
		virtual std::shared_ptr<Window> getWindow() = 0;
	};

}