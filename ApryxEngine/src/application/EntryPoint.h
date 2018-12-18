#pragma once

#include "Application.h"

std::shared_ptr<apryx::Application> createApplication();

#if true //TODO if windows platform

#include "opengl/GLGraphics2D.h"
#include "win32/Win32Timer.h"
#include "win32/Win32Window.h"
#include "win32/Win32Context.h"

int main()
{
	using namespace apryx;

	auto window = std::make_shared<Win32Window>("Game Window", 1280, 720, false, false);
	auto context = std::make_shared<Win32Context>(window);

	auto application = createApplication();
	application->init(context);

	window->setVisible(true);

	GLGraphics2D graphics(window);

	Win32Timer timer;
	timer.start();

	double sum = 0;

	double secondCount = 0;
	int fps = 0;

	const bool useDtMax = true;

	double dtMax = 1.0 / 60.0;

	while (!application->shouldQuit()) {
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

				application->update();
				context->input.clear();

				sum -= dtMax;
			}
		}
		else {
			context->deltaTime = (float)delta;
			context->runTime += (float)dtMax;

			application->update();
			context->input.clear();
		}

		if (application->shouldRedraw()) {
			context->frameTime = (float)(sum / dtMax);
			
			graphics.reset();

			application->draw(graphics);

			graphics.flush();

			window->swap();

			if (!window->getVSync())
				Win32Timer::sleep(1.0 / 120.0);
		}
		else {
			Win32Timer::sleep(1.0 / 60.0);
		}
	}

	application->destroy();
	window->destroy();

	return 0;
}

#endif