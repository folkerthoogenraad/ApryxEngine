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

		Timer timer;
		timer.start();

		float sum = 0;

		const bool useDtMax = true;

		float dtMax = 1.0f / 20.0f;

		while (!application.shouldQuit()) {
			window->poll();

			float delta = timer.lap();

			delta = min(delta, 0.25);

			if (useDtMax) {
				sum += delta;

				while (sum > dtMax) {
					application.update(dtMax);
					sum -= dtMax;
				}
			}
			else {
				application.update(delta);
			}

			if (application.shouldRedraw()) {
				application.draw(graphics, sum / dtMax);

				graphics.flush();
				window->swap();
				// TODO check for vsync
			}
			else {
				Timer::sleep(1.0 / 60.0);
			}
		}

		application.destroy();
		window->destroy();
	}

}