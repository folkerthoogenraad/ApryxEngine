#include "win32/Win32Window.h"
#include <iostream>

#include "time\Timer.h"
#include "opengl/GLGraphics2D.h"
#include "math/math.h"

int main()
{
	using namespace apryx;

	Win32Window window("Not yet OpenGL window", 1280, 720, false);
	window.setVisible(true);

	GLGraphics2D graphics;

	float x = 0;
	
	while (!window.isCloseRequested()) {
		window.poll();
		x += 1;

		graphics.drawClear();
		graphics.setSize(1280/5, 720/5);
		
		Paint paint;
		paint.setColor(Color32::red());

		paint.setColor(Color32::red());
		graphics.drawSpiral(paint, Vector2f(128, 48), 16, 32, 3.14, sin(x / 10) * PI * 2);

		graphics.flush();

		window.swap();

		Timer::sleep(0.2);
	}

	window.destroy();

	return 0;

}