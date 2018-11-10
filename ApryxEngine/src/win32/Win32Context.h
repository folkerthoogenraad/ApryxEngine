#pragma once

#include "resources/Context.h"

#include <memory>
#include <map>
#include <string>

namespace apryx {

	class Win32Context : public Context{
		std::shared_ptr<Window> m_Window;

		std::shared_ptr<Font> m_DefaultFont;

		std::map<std::string, std::weak_ptr<Texture>> m_Textures;
		std::map<std::pair<std::string, int>, std::weak_ptr<Font>> m_Fonts;
	public:
		Win32Context(std::shared_ptr<Window> window);

		virtual std::shared_ptr<Window> getWindow() { return m_Window; }
		virtual std::shared_ptr<Font> getDefaultFont() override;

		// Loading GPU resources
		virtual std::shared_ptr<Texture> loadTexture(std::string path) override;
		virtual std::shared_ptr<Font> loadFont(std::string path, int points) override;

		// Loading CPU resources (uncached)
		virtual Image loadImage(std::string path) override;

		// Creating resources
		virtual std::shared_ptr<Surface> createSurface(int width, int height) override;
		virtual std::shared_ptr<Texture> createTexture() override;
	};

}