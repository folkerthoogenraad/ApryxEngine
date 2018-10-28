#pragma once

#include "resources/ResourceManager.h"

#include <memory>
#include <map>
#include <string>

namespace apryx {

	class Win32ResourceManager : public ResourceManager{
		std::shared_ptr<Window> m_Window;

		std::map<std::string, std::weak_ptr<Texture>> m_Textures;
	public:
		Win32ResourceManager(std::shared_ptr<Window> window);

		virtual std::shared_ptr<Window> getWindow() { return m_Window; }

		// Loading GPU resources
		virtual std::shared_ptr<Texture> loadTexture(std::string path) override;

		// Loading CPU resources (uncached)
		virtual Image loadImage(std::string path) override;

		// Creating resources
		virtual std::shared_ptr<Surface> createSurface(int width, int height) override;
		virtual std::shared_ptr<Texture> createTexture() override;
	};

}