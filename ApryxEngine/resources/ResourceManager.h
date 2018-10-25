#pragma once

#include <memory>

#include "graphics/Window.h"
#include "graphics/Texture.h"

namespace apryx {

	class ResourceManager {
	public:
		virtual std::shared_ptr<Window> getWindow() = 0;


		// Only use when you are sure this is good
		virtual std::shared_ptr<Texture> createTexture() = 0;
	};

}