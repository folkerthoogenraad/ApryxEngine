#include "win32/Win32Window.h"
#include "win32/Win32Engine.h"

#include <iostream>

#include "console/Console.h"

#include "time\Timer.h"
#include "opengl/GLGraphics2D.h"
#include "math/math.h"

#include "graphics/Camera2D.h"
#include "graphics/Image.h"

#include "time/Timer.h"

#include "game/Game.h"

#include <assert.h>
#include <fstream>

#include "EntityPlayer.h"
#include "EntityWall.h"

#include "graphics/FontUtils.h"

namespace apryx {
	class TestGame : public Game {
	public:
		std::shared_ptr<Context> m_Context;

		Scene m_Scene;

		virtual void init(std::shared_ptr<Context> context)
		{
			m_Context = context;
			m_Scene.init(context);

			Console::log("Init all");

			for (int i = 0; i < 20; i++) {
				auto wall = std::make_shared<EntityWall>();
				wall->position = Vector2f(16 + i * 16, 128);
				Console::log("Creating wall...");

				m_Scene.addEntity(wall);
			}

			{
				auto wall = std::make_shared<EntityWall>();
				wall->position = Vector2f(128, 128 - 16);

				m_Scene.addEntity(wall); 
			}

			for (int i = 0; i < 1; i++) {
				auto entity = std::make_shared<EntityPlayer>();
				entity->position = Vector2f(48 + i * 32, 48);
				m_Scene.addEntity(entity);
			}
			
		}

		virtual void draw(Graphics2D &graphics)
		{
			graphics.drawClear(Color32::white());

			float aspect = m_Context->getWindow()->getWidth() / m_Context->getWindow()->getHeight();
			float width = 480;
			float height = width / aspect;

			graphics.setCamera(Camera2D(width, height, false));

			m_Scene.draw(graphics);

			Paint fontPaint(Color32::green());
			fontPaint.setFont(m_Context->getDefaultFont());

			const float scale = 2;

			graphics.setCamera(Camera2D(m_Context->getWindow()->getRawWidth() / scale, m_Context->getWindow()->getRawHeight() / scale, false));
			graphics.drawConsole(Paint(Color32(0,0,0,128)), fontPaint);

			graphics.flush();
		}

		virtual void update() {
			m_Scene.update();

		}
		virtual void destroy() { }

		virtual bool shouldQuit() { return m_Context->getWindow()->isCloseRequested(); }
	};
}

int main()
{
	using namespace apryx;

	startWin32Application<TestGame>();

	Console::pause();

	return 0;
}