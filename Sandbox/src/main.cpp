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

#include "ui/ApryxUI.h"
#include "ui/Button.h"
#include "ui/LinearLayout.h"

namespace apryx {
	class TestGame : public Game {
	public:
		std::shared_ptr<ApryxUI> ui;

		virtual void init(std::shared_ptr<Context> context)
		{
			Game::init(context);

			ui = std::make_shared<ApryxUI>(context);

			ui->getStyle().textFont = context->loadFont("fonts/OpenSans.ttf", (int)(16));
			ui->getStyle().componentFont = context->loadFont("fonts/Exo2.ttf", (int)(16));

			auto layout = std::make_shared<LinearLayout>(LinearLayout::Horizontal);
			layout->setGap(40);

			auto buttonSubmit = std::make_shared<Button>("Submit", Button::Primary);
			buttonSubmit->setLayoutParams(LayoutParams(LayoutParams::MatchParent, LayoutParams::WrapContent, Vector2f(2, 1)));

			auto buttonCancel = std::make_shared<Button>("Cancel", Button::Secondary);
			buttonCancel->setLayoutParams(LayoutParams(LayoutParams::WrapContent, LayoutParams::WrapContent, Vector2f(1,1)));

			layout->addComponent(buttonCancel);
			layout->addComponent(buttonSubmit);

			ui->setMainComponent(layout);

			ui->updateLayout(context->getWindow()->getWidth(), context->getWindow()->getHeight());
		}

		virtual void draw(Graphics2D &graphics)
		{
			graphics.setCamera(Camera2D(m_Context->getWindow()->getWidth(), m_Context->getWindow()->getHeight(), false));
			graphics.drawClear(Color32::white());

			ui->draw(graphics);
		}

		virtual void update() {
			ui->update();
		}
	};
}



std::shared_ptr<apryx::Application> createApplication()
{
	return std::make_shared<apryx::TestGame>();
}