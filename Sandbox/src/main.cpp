#include <iostream>
#include <memory>

#include "math/math.h"

#include "opengl/GLGraphics2D.h"

#include "graphics/Camera2D.h"
#include "graphics/Image.h"

#include "graphics/Font.h"
#include "graphics/FontUtils.h"

#include "game/Game.h"

#include "EntityPlayer.h"
#include "EntityWall.h"

#include "application/EntryPoint.h"

namespace apryx {
	class TestGame : public Game {
	public:
		Scene2D m_Scene;
		std::shared_ptr<Font> m_ButtonFont;
		std::shared_ptr<Font> m_ContentFont;

		virtual void init(std::shared_ptr<Context> context)
		{
			Game::init(context);
			m_Scene.init(context);

			m_ButtonFont = context->loadFont("fonts/Exo2.ttf", 16);
			m_ContentFont = context->loadFont("fonts/OpenSans.ttf", 16);

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

			Paint fontPaint(Color32(128, 160, 128, 255));
			fontPaint.setVerticalAlignment(Paint::VAlign::Center);
			fontPaint.setHorizontalAlignment(Paint::HAlign::Center);
			fontPaint.setFont(m_ButtonFont);

			const float scale = 1;

			graphics.setCamera(Camera2D(m_Context->getWindow()->getRawWidth() / scale, m_Context->getWindow()->getRawHeight() / scale, false));


			Paint linePaint(Color32(128, 160, 128, 255));
			linePaint.setStrokeWidth(1);
			linePaint.setStyle(Paint::Stroke);

			Vector2f offset = Vector2f(256, 256);

			graphics.drawRoundedRectangle(linePaint, Rectanglef(12, 12, 128, 40), 20);
			graphics.drawText(fontPaint, Rectanglef(12, 12, 128, 40).center(), "Cancel");

			fontPaint.setColor(Color32::white());
			linePaint.setStyle(Paint::Fill);

			graphics.drawRoundedRectangle(linePaint, Rectanglef(150, 12, 128, 40), 20);
			graphics.drawText(fontPaint, Rectanglef(150, 12, 128, 40).center(), "Submit");

			fontPaint.setFont(m_ContentFont);
			fontPaint.setVerticalAlignment(Paint::VAlign::Top);
			fontPaint.setHorizontalAlignment(Paint::HAlign::Left);
			fontPaint.setColor(Color32::gray());
			graphics.drawText(fontPaint, Vector2f(16, 64),
				"This is some testing content that might actually work pretty well.\n"
				"I'm not to sure what to write here so this might be the best thing\n"
				"so far. \n"
				"The ApryxEngine is actually kinda amazing. lul\n");



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