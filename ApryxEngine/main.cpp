#include "win32/Win32Window.h"
#include "win32/Win32Engine.h"

#include <iostream>

#include "opengl/GLGraphics2D.h"

#include "graphics/Camera2D.h"
#include "graphics/Image.h"

#include "time/Timer.h"

#include "game/Game.h"

namespace apryx {
	class TestGame : public Game {
	public:
		std::shared_ptr<ResourceManager> m_Manager;
		
		virtual void init(std::shared_ptr<ResourceManager> manager) 
		{
			m_Manager = manager;
		}

		virtual void draw(Graphics2D &graphics)
		{
			Camera2D camera(m_Manager->getWindow()->getWidth(), m_Manager->getWindow()->getHeight());
			graphics.setCamera(camera);

			Paint paint;

			graphics.drawClear();
			graphics.drawRectangle(paint, Rectanglef(0, 0, 16, 16));
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

	std::cout << "Pest." << std::endl;
	std::cin.get();

	Win32Window window("Game Window", 1280, 720, true);
	window.setVisible(true);

	Image image = Image::checkerboard(8, 8, Color32::red(), Color32::white());

	std::shared_ptr<GLTexture> texture = std::make_shared<GLTexture>();
	texture->setData(image);

	Sprite sprite = Sprite(texture);
	sprite.setOrigin(Vector2f(4, 4));

	GLGraphics2D graphics;

	Camera2D camera(window.getWidth() / 5, window.getHeight() / 5);
	graphics.setCamera(camera);

	float angle = 0;
	
	Timer timer;
	timer.start();

	while (!window.isCloseRequested()) {
		window.poll();

		float delta = timer.lap();
		angle += delta * 360 / 4;

		graphics.drawClear();
		
		Paint paint;
		
		graphics.drawRectangle(paint, Rectanglef(0, 0, camera.getWidth(), 16));
		graphics.drawSprite(paint, sprite, Vector2f(24, 24), Vector2f(1, 1), angle);

		graphics.flush();

		window.swap();
	}

	window.destroy();

	return 0;

}