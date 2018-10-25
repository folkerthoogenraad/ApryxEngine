#include "win32/Win32Window.h"
#include "win32/Win32Engine.h"

#include <iostream>

#include "time\Timer.h"
#include "opengl/GLGraphics2D.h"
#include "math/math.h"

#include "graphics/Camera2D.h"
#include "graphics/Image.h"

#include "time/Timer.h"

#include "game/Game.h"

namespace apryx {
	class TestGame : public Game {
	public:
		std::shared_ptr<ResourceManager> m_Manager;
		std::shared_ptr<Texture> m_Texture;
		
		virtual void init(std::shared_ptr<ResourceManager> manager) 
		{
			m_Manager = manager;

			Image image = Image::checkerboard(2, 2);

			m_Texture = m_Manager->createTexture();
			m_Texture->setData(image);
		}

		virtual void draw(Graphics2D &graphics)
		{
			Camera2D camera(m_Manager->getWindow()->getWidth() / 5, m_Manager->getWindow()->getHeight() / 5);
			graphics.setCamera(camera);

			Sprite sprite(m_Texture);

			Paint paint;

			graphics.drawClear();
			graphics.drawRectangle(paint, Rectanglef(0, 0, 16, 16));

			graphics.drawSprite(paint, sprite, Vector2f(48, 48));
		}

		virtual void update() { }
		virtual void destroy() { }

		virtual bool shouldQuit() { return m_Manager->getWindow()->isCloseRequested(); }
	};
}

int main()
{
	using namespace apryx;

	startWin32Application<TestGame>();

	return 0;
}