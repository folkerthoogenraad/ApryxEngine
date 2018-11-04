#include "Graphics2D.h"

#include "console/Console.h"

namespace apryx {
	void apryx::Graphics2D::drawConsole(const Paint &background, const Paint &foreground)
	{
		drawRectangle(background, Rectanglef(4, 4, 512, 256));

		Vector2f position;
		position.x = 6;
		position.y = 6;

		for (auto &str : Console::history) {
			drawText(foreground, position, str);
			position.y += 6;
		}
	}
}
