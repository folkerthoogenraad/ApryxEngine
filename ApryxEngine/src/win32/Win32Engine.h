#pragma once


#include "opengl/GLGraphics2D.h"
#include "Win32Timer.h"
#include "Win32Context.h"

namespace apryx {

	template<class T>
	void startWin32Application() 
	{
		auto window = std::make_shared<Win32Window>("Game Window", 1280, 720, false, false);
		auto context = std::make_shared<Win32Context>(window);

		T application;
		application.init(context);

		window->setVisible(true);

		GLGraphics2D graphics(window);

		Win32Timer timer;
		timer.start();

		double sum = 0;

		double secondCount = 0;
		int fps = 0;

		const bool useDtMax = true;

		double dtMax = 1.0 / 60.0;

		while (!application.shouldQuit()) {
			window->poll();

			context->input.processEvents(window->getWindowEvents());

			double delta = timer.lap();

			secondCount += delta;
			fps++;

			if (secondCount > 1) {
				secondCount -= 1;
				std::cout << "Frames: " << fps << std::endl;
				fps = 0;
			}

			delta = min(delta, 0.25);

			if (useDtMax) {
				sum += delta;

				while (sum > dtMax) {
					context->deltaTime = (float)dtMax;
					context->runTime += (float)dtMax;

					application.update();
					context->input.clear();

					sum -= dtMax;
				}
			}
			else {
				context->deltaTime = (float)delta;
				context->runTime += (float)dtMax;

				application.update();
				context->input.clear();
			}

			if (application.shouldRedraw()) {
				context->frameTime = (float)sum / dtMax;
				application.draw(graphics);

				graphics.flush();

				window->swap();

				if(!window->getVSync())
					Win32Timer::sleep(0.004);
			}
			else {
				Timer::sleep(1.0 / 60.0);
			}
		}

		application.destroy();
		window->destroy();
	}

}