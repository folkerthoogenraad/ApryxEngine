#include "win32/Win32Window.h"
#include <iostream>

#include "opengl/GLGraphics2D.h"

int main()
{
	using namespace apryx;

	Win32Window window("Not yet OpenGL window", 1280, 720, false);
	window.setVisible(true);

	GLGraphics2D graphics;
	

	while (!window.isCloseRequested()) {
		window.poll();

		graphics.drawClear();
		graphics.setSize(320, 160);
		
		Paint paint;
		paint.setColor(Color32::red());

		graphics.drawRectangle(paint, Rectanglef(0, 0, 16, 16));

		graphics.flush();

		window.swap();
	}

	window.destroy();

	return 0;

}