#include <iostream>
#include <memory>

#include "application/EntryPoint.h"
#include "game/Game.h"

namespace apryx {
	class TestGame : public Game {
	public:
		virtual void init(std::shared_ptr<Context> context)
		{
			Game::init(context);
		}

		virtual void draw(Graphics2D &graphics)
		{
			graphics.drawClear(Color32::blue());
		}

		virtual void update() {
		}
	};
}



std::shared_ptr<apryx::Application> createApplication()
{
	return std::make_shared<apryx::TestGame>();
}