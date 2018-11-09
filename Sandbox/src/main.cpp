#include <iostream>

#include "math/math.h"

#include "opengl/GLGraphics2D.h"

#include "graphics/Camera2D.h"
#include "graphics/Image.h"

#include "game/Game.h"

#include "EntityPlayer.h"
#include "EntityWall.h"

#include "application/EntryPoint.h"

namespace apryx {
	class TestGame : public Game {
	public:
		Scene2D m_Scene;

		virtual void init(std::shared_ptr<Context> context)
		{
			Game::init(context);
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


			{
				auto wall = std::make_shared<EntityWall>();
				wall->position = Vector2f(128 + 64, 128 - 16);

				m_Scene.addEntity(wall);
			}


			{
				auto wall = std::make_shared<EntityWall>();
				wall->position = Vector2f(128 + 64, 128 - 32);

				m_Scene.addEntity(wall);
			}

			auto entity = std::make_shared<EntityPlayer>();
			entity->position = Vector2f(48 + 32, 48);
			m_Scene.addEntity(entity);
			
		}

		virtual void draw(Graphics2D &graphics)
		{
			graphics.drawClear(Color32::white());

			float aspect = m_Context->getWindow()->getWidth() / m_Context->getWindow()->getHeight();
			float width = 480;
			float height = width / aspect;

			graphics.setCamera(Camera2D(width, height, false));

			m_Scene.draw(graphics);

			Paint fontPaint(Color32::black());
			fontPaint.setVerticalAlignment(Paint::VAlign::Center);
			fontPaint.setHorizontalAlignment(Paint::HAlign::Center);
			fontPaint.setFont(m_Context->getDefaultFont());

			const float scale = 1;

			graphics.setCamera(Camera2D(m_Context->getWindow()->getRawWidth() / scale, m_Context->getWindow()->getRawHeight() / scale, false));
			graphics.drawText(fontPaint, Vector2f(2,2), "Test text 123");


			Paint linePaint(Color32(128, 160, 128, 255));
			linePaint.setStrokeWidth(1);
			linePaint.setStyle(Paint::Stroke);

			Vector2f offset = Vector2f(256, 256);

			graphics.drawLine(linePaint, offset + Vector2f(2, 2), offset + Vector2f(16, 32));
			graphics.drawLine(linePaint, offset + Vector2f(16, 2), offset + Vector2f(48, 32));

			graphics.drawRectangle(linePaint, Rectanglef(150, 12, 128, 64));
			graphics.drawRoundedRectangle(linePaint, Rectanglef(12, 12, 128, 40), 20);
			graphics.drawText(fontPaint, Rectanglef(12, 12, 128, 40).center(), "Test text");
			graphics.drawElipse(linePaint, Rectanglef(300, 12, 64, 64));


			graphics.drawLine(linePaint, Vector2f(100, 100), Vector2f(200, 100));
			graphics.drawLine(linePaint, Vector2f(100, 100), Vector2f(100, 200));


			graphics.flush();
		}

		virtual void update() {
			m_Scene.update();

		}
	};
}



std::shared_ptr<apryx::Application> createApplication()
{
	return std::make_shared<apryx::TestGame>();
}