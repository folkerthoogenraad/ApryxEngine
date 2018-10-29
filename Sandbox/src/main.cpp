#include "win32/Win32Window.h"
#include "win32/Win32Engine.h"

#include <iostream>

#include "log/Log.h"

#include "time\Timer.h"
#include "opengl/GLGraphics2D.h"
#include "math/math.h"

#include "graphics/Camera2D.h"
#include "graphics/Image.h"

#include "time/Timer.h"

#include "game/Game.h"

#include <assert.h>

namespace apryx {
	class TestGame : public Game {
	public:
		std::shared_ptr<ResourceManager> m_Manager;
		std::shared_ptr<Texture> m_Texture;
		std::shared_ptr<Surface> m_Surface;

		float previousX = 0;
		float x = 0;

		Sprite sprite;

		virtual void init(std::shared_ptr<ResourceManager> manager)
		{
			m_Manager = manager;

			m_Texture = m_Manager->loadTexture("Player.png");

			m_Surface = m_Manager->createSurface(32, 32);
		}

		virtual void draw(Graphics2D &graphics, float frame)
		{
			Sprite sprite(m_Texture);

			Paint paint(Color32::white());

			m_Surface->getGraphics().drawClear(Color32::blue());
			m_Surface->getGraphics().drawSprite(Paint(Color32::white()), sprite, Vector2f(0, 0));
			m_Surface->getGraphics().drawCircle(Paint(Color32::white()), Vector2f(16, 16), 8);
			m_Surface->getGraphics().flush();

			Sprite sprite2(m_Surface);
			graphics.drawSprite(paint, sprite2, Vector2f(0, 0));

			graphics.drawSurface(paint, *m_Surface, Vector2f(0, 0));

			graphics.setCamera(Camera2D(128, 72));
			graphics.drawClear(Color32::white());

			graphics.drawSprite(Paint(Color32::white()), sprite, Vector2f(lerp(previousX, x, frame), 48));
			
			graphics.flush();
		}

		virtual void update(float delta) {
			previousX = x;

			x += delta * 80;

			if (x > 128)
				x = 0;
		}
		virtual void destroy() { }

		virtual bool shouldQuit() { return m_Manager->getWindow()->isCloseRequested(); }
	};
}

int main()
{
	using namespace apryx;

	startWin32Application<TestGame>();

	Debug::pause();

	return 0;
}