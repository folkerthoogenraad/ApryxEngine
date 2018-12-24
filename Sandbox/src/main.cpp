#include <iostream>
#include <memory>

#include "application/EntryPoint.h"

#if 0

#include "game/Game.h"
#include "ecs/Component.h"
#include "ecs/EntityComponentSystem.h"

namespace apryx {

	static float random_f() {
		return rand() / (float)RAND_MAX;
	}

	struct Transform : public Component {
		Vector2f position;
	};

	struct Collider : public Component {
		float width;
		float height;
	};

	struct Moveable : public Component {
		Vector2f velocity;
	};

	struct PlayerInput : public Component {

	};

	struct PlayerMove : public Component {

	};

	struct Renderer : public Component {
		Sprite sprite;
	};

}



namespace apryx {
	class TestGame : public Game {
	public:

		EntityComponentSystem system;

		virtual void init(std::shared_ptr<Context> context)
		{
			Game::init(context);

			float w = context->getWindow()->getWidth();
			float h = context->getWindow()->getHeight();

			for (int i = 0; i < 1000; i++) {
				Entity e = system.createEntity();

				Transform *t = system.addComponent<Transform>(e);
				Renderer *r = system.addComponent<Renderer>(e);
				Moveable *m = system.addComponent<Moveable>(e);

				t->position = Vector2f(random_f() * w, random_f() * h);
				m->velocity = Vector2f(random_f() * 500 - 250, random_f() * 500 - 250);

				r->sprite = Sprite(context->loadTexture("sprites/characters/Player1.png"), 0, 0, 16, 16);
			}
		}

		virtual void draw(Graphics2D &graphics) {
			graphics.drawClear(Color32::white());

			system.process<Transform, Renderer>([&](auto entity, auto &transform, auto &renderer) {
				graphics.drawSprite(Paint(), renderer.sprite, transform.position);
			});

		}

		virtual void update() {
			float w = m_Context->getWindow()->getWidth();
			float h = m_Context->getWindow()->getHeight();
			
			system.process<Transform, Moveable>([&](auto entity, auto &transform, auto &moveable) {
				transform.position += moveable.velocity * m_Context->deltaTime;

				if (transform.position.x < 0) transform.position.x += w;
				if (transform.position.x > w) transform.position.x -= w;
				if (transform.position.y < 0) transform.position.y += h;
				if (transform.position.y > h) transform.position.y -= h;
			});
		}
	};
}

std::shared_ptr<apryx::Application> createApplication()
{
	return std::make_shared<apryx::TestGame>();
}


#elif 0

#include "city\CityApplication.h"

std::shared_ptr<apryx::Application> createApplication()
{
	return std::make_shared<apryx::CityApplication>();
}

#elif 0

#include "gui/GUIApplication.h"

std::shared_ptr<apryx::Application> createApplication()
{
	return std::make_shared<apryx::GUIApplication>();
}


#elif 1

#include "physics/PhysicsApp.h"

std::shared_ptr<apryx::Application> createApplication()
{
	return std::make_shared<apryx::PhysicsApp>();
}

#endif
