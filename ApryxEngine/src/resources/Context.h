#pragma once

#include <memory>

#include "graphics/Window.h"
#include "graphics/Texture.h"
#include "graphics/Surface.h"
#include "graphics/Image.h"

#include "game/SceneLoader.h"
#include "input/InputManager.h"

namespace apryx {

	class Context {
		SceneLoader m_SceneLoader;
	public:
		// Time
		float deltaTime = 0;
		float frameTime = 0; // Frame Advance Time (interpolation time lerp(previousX, x, frameTime))
		float runTime = 0;

		InputManager input;

		virtual std::shared_ptr<Window> getWindow() = 0;
		virtual std::shared_ptr<Font> getDefaultFont() = 0;

		// Misc
		SceneLoader &getSceneLoader() { return m_SceneLoader; }
		const SceneLoader &getSceneLoader() const { return m_SceneLoader; }

		// Loading resources, cached
		virtual std::shared_ptr<Texture> loadTexture(std::string path) = 0;
		virtual std::shared_ptr<Font> loadFont(std::string path, int points) = 0;

		// Loading raw resources (CPU side, uncached)
		virtual Image loadImage(std::string path) = 0;

		// Only use when you are sure this is good
		virtual std::shared_ptr<Texture> createTexture() = 0;
		virtual std::shared_ptr<Surface> createSurface(int width, int height) = 0;
	};

}