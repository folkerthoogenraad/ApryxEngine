#pragma once

#include "time/Timer.h"

#include "opengl/GLGraphics2D.h"
#include "Win32ResourceManager.h"

namespace apryx {

	template<class T>
	void startWin32Application() 
	{
		auto window = std::make_shared<Win32Window>("Game Window", 1280, 720, true);
		auto manager = std::make_shared<Win32ResourceManager>(window);

		T application;
		application.init(manager);

		window->setVisible(true);

		GLGraphics2D graphics(window);

		while (!application.shouldQuit()) {
			window->poll();

			application.update();

			if (application.shouldRedraw()) {
				application.draw(graphics);

				graphics.flush();
				window->swap();
			}
			else {
				Timer::sleep(1.0 / 60.0);
			}
		}

		application.destroy();
		window->destroy();
	}

}