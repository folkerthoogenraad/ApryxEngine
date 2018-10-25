#include "Win32ResourceManager.h"

#include "opengl/GLTexture.h"
#include "opengl/GLSurface.h"

namespace apryx {
	Win32ResourceManager::Win32ResourceManager(std::shared_ptr<Window> window)
		: m_Window(window)
	{
	}
	std::shared_ptr<Texture> Win32ResourceManager::createTexture()
	{
		return std::make_shared<GLTexture>();
	}
	std::shared_ptr<Surface> Win32ResourceManager::createSurface(int width, int height)
	{
		return std::make_shared<GLSurface>(width, height);
	}
}
