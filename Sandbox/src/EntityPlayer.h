#pragma once

#include "scene/Entity.h"
#include "scene/Scene.h"

namespace apryx {

	class EntityPlayer : public Entity {
		Sprite sprite;

		Vector2f previousPosition;

		Vector2f position;
		Vector2f velocity;

		Vector2f drawScale = Vector2f(1, 1);

		float movementSpeed = 3 * 60;
		float gravity = 30 * 60;
	public:
		virtual void init(Scene *m_Scene) override;
		virtual void update() override;
		virtual void draw(Graphics2D &graphics) override;

	};

}