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

#include "EntityPlayer.h"

namespace apryx {
	class TestGame : public Game {
	public:
		std::shared_ptr<Context> m_Context;
		Scene m_Scene;

		virtual void init(std::shared_ptr<Context> context)
		{
			m_Context = context;
			m_Scene.init(context);
			m_Scene.addEntity(std::make_shared<EntityPlayer>());
		}

		virtual void draw(Graphics2D &graphics)
		{
			graphics.drawClear(Color32::white());

			float aspect = m_Context->getWindow()->getWidth() / m_Context->getWindow()->getHeight();
			float width = 480;
			float height = width / aspect;

			graphics.setCamera(Camera2D(width, height, false));

			m_Scene.draw(graphics);

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

	Debug::pause();

	return 0;
}