#pragma once

#include "scene/Entity.h"
#include "scene/Scene.h"

#include "graphics/Sprite.h"
#include "graphics/Animation.h"
#include "graphics/AnimationController.h"

#include "math/collision.h"


namespace apryx {

	class EntityPlayer : public Entity {
		AnimationController controller;

		Vector2f velocity;
		Vector2f drawScale = Vector2f(1, 1);

		float movementSpeed = 1.5f * 60;		// Pixel per second
		float gravity = 0.25f * 60 * 60;		// Pixels per second^2

		float gravityUpFraciton = 0.5f;

		bool grounded = false;
		
		// Jumping
		bool jumped = false;
		bool jumpHop = false;
	public:
		virtual void init(Scene *m_Scene) override;
		virtual void update() override;
		virtual void draw(Graphics2D &graphics) override;

		virtual std::optional<Rectanglef> getBoundingBox() const override;
	private:
		void applyGravity();
		void applyMotion();

		void updateJump();
		void updateMove();

		void updateAnimation();

	};

}