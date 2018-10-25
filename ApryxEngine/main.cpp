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
		std::shared_ptr<Surface> m_Surface;
		
		virtual void init(std::shared_ptr<ResourceManager> manager) 
		{
			m_Manager = manager;

			Image image = Image::colored(4, 4, Color32::green());

			image.setColor(0, 3, Color32::red());

			m_Texture = m_Manager->createTexture();
			m_Texture->setData(image);

			m_Surface = m_Manager->createSurface(32, 32);
		}

		virtual void draw(Graphics2D &graphics)
		{
			Sprite sprite(m_Texture);
			Sprite sprite2(m_Surface->getTexture());

			Paint paint(Color32::white());

			m_Surface->getGraphics().drawClear(Color32::blue());
			m_Surface->getGraphics().drawCircle(paint, Vector2f(16, 16), 16);
			m_Surface->getGraphics().flush();

			graphics.setCamera(Camera2D(128, 72));
			graphics.drawClear(Color32::white());

			graphics.drawSprite(paint, sprite, Vector2f(48, 48));
			graphics.drawSprite(paint, sprite2, Vector2f(48, 0));

			graphics.flush();
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