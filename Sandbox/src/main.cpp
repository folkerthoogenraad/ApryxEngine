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
#include "EntityWall.h"

namespace apryx {
	class TestGame : public Game {
	public:
		std::shared_ptr<Context> m_Context;
		std::shared_ptr<Font> m_Font;
		Scene m_Scene;

		virtual void init(std::shared_ptr<Context> context)
		{
			m_Context = context;
			m_Scene.init(context);

			for (int i = 0; i < 20; i++) {
				auto wall = std::make_shared<EntityWall>();
				wall->position = Vector2f(16 + i * 16, 128);

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


			FontBuilder builder(m_Context->loadTexture("fonts/fFont.png"));
			builder.setHeight(5);
			builder.setLineSpacing(1);

			builder.addChar('A', 3, 5, 4, 0, 0, 4);
			builder.addChar('B', 3, 5, 4, 0, 0, 4);
			builder.addChar('C', 3, 5, 4, 0, 0, 4);
			builder.addChar('D', 3, 5, 4, 0, 0, 4);
			builder.addChar('E', 3, 5, 4, 0, 0, 4);
			builder.addChar('F', 3, 5, 4, 0, 0, 4);
			builder.addChar('G', 3, 5, 4, 0, 0, 4);
			builder.addChar('H', 3, 5, 4, 0, 0, 4);

			builder.newLine();

			builder.addChar('I', 3, 5, 4, 0, 0, 4);
			builder.addChar('J', 3, 5, 4, 0, 0, 4);
			builder.addChar('K', 3, 5, 4, 0, 0, 4);
			builder.addChar('L', 3, 5, 4, 0, 0, 4);
			builder.addChar('M', 5, 5, 6, 0, 0, 6);
			builder.addChar('N', 4, 5, 5, 0, 0, 5);
			builder.addChar('O', 4, 5, 5, 0, 0, 5);

			builder.newLine();

			builder.addChar('P', 3, 5, 4, 0, 0, 4);
			builder.addChar('Q', 3, 5, 4, 0, 0, 4);
			builder.addChar('R', 3, 5, 4, 0, 0, 4);
			builder.addChar('S', 3, 5, 4, 0, 0, 4);
			builder.addChar('T', 3, 5, 4, 0, 0, 4);
			builder.addChar('U', 3, 5, 4, 0, 0, 4);
			builder.addChar('V', 3, 5, 4, 0, 0, 4);

			builder.newLine();

			builder.addChar('W', 5, 5, 6, 0, 0, 6);
			builder.addChar('X', 3, 5, 4, 0, 0, 4);
			builder.addChar('Y', 3, 5, 4, 0, 0, 4);
			builder.addChar('Z', 3, 5, 4, 0, 0, 4);

			builder.newLine();

			builder.addChar('a', 3, 5, 4, 0, 0, 4);
			builder.addChar('b', 3, 5, 4, 0, 0, 4);
			builder.addChar('c', 2, 5, 3, 0, 0, 3);
			builder.addChar('d', 3, 5, 4, 0, 0, 4);
			builder.addChar('e', 3, 5, 4, 0, 0, 4);
			builder.addChar('f', 2, 5, 3, 0, 0, 3);
			builder.addChar('g', 3, 5, 4, 0, 1, 4);
			builder.addChar('h', 3, 5, 4, 0, 0, 4);
			builder.addChar('i', 1, 5, 2, 0, 0, 2);

			builder.newLine();

			builder.addChar('j', 2, 6, 2, -1, 0, 3);
			builder.addChar('k', 3, 5, 4, 0, 0, 4);
			builder.addChar('l', 1, 5, 2, 0, 0, 2);
			builder.addChar('m', 5, 5, 6, 0, 0, 6);
			builder.addChar('n', 3, 5, 4, 0, 0, 4);
			builder.addChar('o', 3, 5, 4, 0, 0, 4);
			builder.addChar('p', 3, 5, 4, 0, 1, 4);
			builder.addChar('q', 3, 5, 4, 0, 1, 4);

			builder.newLine();

			builder.addChar('r', 2, 5, 3, 0, 0, 3);
			builder.addChar('s', 3, 5, 4, 0, 0, 4);
			builder.addChar('t', 2, 5, 3, 0, 0, 3);
			builder.addChar('u', 3, 5, 4, 0, 0, 4);
			builder.addChar('v', 3, 5, 4, 0, 0, 4);
			builder.addChar('w', 5, 5, 6, 0, 0, 6);
			builder.addChar('x', 3, 5, 4, 0, 0, 4);

			builder.newLine();

			builder.addChar('y', 3, 5, 4, 0, 1, 4);
			builder.addChar('z', 3, 5, 4, 0, 0, 4);

			builder.newLine();

			builder.addChar('1', 3, 5, 4, 0, 0, 4);
			builder.addChar('2', 3, 5, 4, 0, 0, 4);
			builder.addChar('3', 3, 5, 4, 0, 0, 4);
			builder.addChar('4', 3, 5, 4, 0, 0, 4);
			builder.addChar('5', 3, 5, 4, 0, 0, 4);
			builder.addChar('6', 3, 5, 4, 0, 0, 4);
			builder.addChar('7', 3, 5, 4, 0, 0, 4);
			builder.addChar('8', 3, 5, 4, 0, 0, 4);

			builder.newLine();

			builder.addChar('9', 3, 5, 4, 0, 0, 4);
			builder.addChar('0', 3, 5, 4, 0, 0, 4);

			builder.newLine();

			builder.addChar('(', 2, 5, 3, 0, 0, 3);
			builder.addChar(')', 2, 5, 3, 0, 0, 3);
			builder.addChar('<', 3, 5, 4, 0, 0, 4);
			builder.addChar('>', 3, 5, 4, 0, 0, 4);
			builder.addChar('[', 2, 5, 3, 0, 0, 3);
			builder.addChar(']', 2, 5, 3, 0, 0, 3);
			builder.addChar('{', 3, 5, 4, 0, 0, 4);
			builder.addChar('}', 3, 5, 4, 0, 0, 4);

			builder.newLine();

			builder.addChar('=', 3, 5, 4, 0, 0, 4);
			builder.addChar('+', 3, 5, 4, 0, 0, 4);
			builder.addChar('-', 3, 5, 4, 0, 0, 4);
			builder.addChar('*', 3, 5, 4, 0, 0, 4);
			builder.addChar('/', 3, 5, 4, 0, 0, 4);
			builder.addChar('\\', 3, 5, 4, 0, 0, 4);
			builder.addChar(':', 1, 5, 2, 0, 0, 2);
			builder.addChar(';', 2, 5, 3, 0, 0, 3);

			builder.newLine();

			builder.addChar('|', 1, 5, 2, 0, 0, 2);
			builder.addChar('~', 5, 5, 6, 0, 0, 6);
			builder.addChar('\_', 3, 5, 4, 0, 0, 4);
			builder.addChar('^', 3, 5, 4, 0, 0, 4);
			builder.addChar('.', 1, 5, 2, 0, 0, 2);
			builder.addChar(',', 2, 5, 2, -1, 1, 3);
			builder.addChar('\'', 1, 5, 2, 0, 0, 2);
			builder.addChar('"', 3, 5, 4, 0, 0, 4);
			builder.addChar('?', 3, 5, 4, 0, 0, 4);
			builder.addChar('!', 1, 5, 2, 0, 0, 2);

			builder.newLine();

			builder.addChar('%', 3, 5, 4, 0, 0, 4);
			builder.addChar('#', 5, 5, 6, 0, 0, 6);

			m_Font = builder.getFont();
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
			fontPaint.setFont(m_Font);

			const float scale = 4;

			graphics.setCamera(Camera2D(m_Context->getWindow()->getRawWidth() / scale, m_Context->getWindow()->getRawHeight() / scale, false));
			graphics.drawText(fontPaint, Vector2f(2, 2), 
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
				"abcdefghijklmnopqrstuvwxyz\n"
				"0123456789\n"
				"Major kudo's if you can read this!\n"
				"If, and only if, this works; it would be: {NICE}.avi \n"
				"SELECT [DIS] <Je moeder> FROM <tabel>\n"
				"0800-1122\n"
				"12x + 3y = 17\n"
				"'this is quoted'?\n"
				"\"This is actually quoted\"! \n"
				"#YOLO #JeMoeder moederpoederaanjevader 20% kans\n"
				"Als dit werkt, dan ga ik dit doen. Je moeder.");

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