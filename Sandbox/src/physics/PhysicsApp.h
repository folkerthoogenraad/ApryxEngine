#pragma once

#include "ecs/EntityComponentSystem.h"
#include "ecs/Component.h"

#include "math/Vector2.h"

#include "application/Application.h"

namespace apryx {

	struct Ball : public Component{
		Vector2f position;
		float radius;
	};

	class PhysicsApp : public Application {
		EntityComponentSystem m_System;

		Entity m_Selected = Entity::None;
	public:
		virtual void init(std::shared_ptr<Context> context) override;

		virtual void draw(Graphics2D &graphics) override;

		virtual void update() override;

		virtual void destroy() override;
	};
}