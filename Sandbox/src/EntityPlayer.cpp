#include "EntityPlayer.h"

#include "math/math.h"
#include "EntityWall.h"

#include "console/Console.h"

namespace apryx {
	void EntityPlayer::init(Scene * scene)
	{
		auto tx = scene->getContext()->loadTexture("sprites/Player1.png");

		Animation idle;
		Animation running;

		Animation jumping;
		Animation falling;

		idle.addSprite(Sprite(tx, 0, 0, 16, 16).setCenter());
		idle.setSpeed(12);

		running.addSprite(Sprite(tx, 0, 16, 16, 16).setCenter());
		running.addSprite(Sprite(tx, 16, 16, 16, 16).setCenter());
		running.addSprite(Sprite(tx, 32, 16, 16, 16).setCenter());
		running.addSprite(Sprite(tx, 48, 16, 16, 16).setCenter());
		running.setSpeed(12);

		jumping.addSprite(Sprite(tx, 0, 48, 16, 16).setCenter());
		jumping.addSprite(Sprite(tx, 16, 48, 16, 16).setCenter());
		jumping.setSpeed(12);

		falling.addSprite(Sprite(tx, 0, 32, 16, 16).setCenter());
		falling.addSprite(Sprite(tx, 16, 32, 16, 16).setCenter());
		falling.setSpeed(12);

		controller.setState("Idle", idle);
		controller.setState("Running", running);
		controller.setState("Jumping", jumping);
		controller.setState("Falling", falling);

		controller.addTransition("Idle", "Running", "hspeed", AnimationTransition::NotEqual, 0);
		controller.addTransition("Running", "Idle", "hspeed", AnimationTransition::Equal, 0);

		controller.addTransition("Jumping", "Falling", "vspeed", AnimationTransition::Greater, 0);
		controller.addTransition("Falling", "Jumping", "vspeed", AnimationTransition::Less, 0);

		controller.addTransition("Jumping", "Idle", "grounded", true);
		controller.addTransition("Falling", "Idle", "grounded", true);

		controller.addTransition("Idle", "Jumping", "grounded", false);
		controller.addTransition("Running", "Jumping", "grounded", false);

		controller.setCurrentState("Idle");

		controller.setValue("hspeed", 0.0f);
		controller.setValue("vspeed", 0.0f);
		controller.setValue("grounded", 0.0f);
	}

	void EntityPlayer::update()
	{
		preUpdate();

		applyGravity();

		updateMove();
		updateJump();

		applyMotion();

		updateAnimation();
	}

	void EntityPlayer::draw(Graphics2D & graphics)
	{
		Context &context = *m_Scene->getContext();

		graphics.drawSprite(Paint(Color32::white()), controller.getCurrentSprite(), getDrawPosition(), drawScale);
	}

	std::optional<Rectanglef> EntityPlayer::getBoundingBox() const
	{
		return Rectanglef(position.x + 3 - 8, position.y + 3 - 8, 10, 13);
	}

	void EntityPlayer::applyGravity()
	{
		auto state = getState();

		if (velocity.y > 0) {
			velocity.y += gravity * state.context.deltaTime;
		}
		else {
			velocity.y += (gravity * (1.0f - gravityUpFraciton)) * state.context.deltaTime;
		}
	}

	void EntityPlayer::applyMotion()
	{
		auto state = getState();

		// X motion
		{
			float currentMotion = velocity.x * state.context.deltaTime;
			bool collided = false;

			Rectanglef bbox = *getBoundingBox();

			m_Scene->forEach<EntityWall>([&](EntityWall &wall) {
				auto t = wall.getBoundingBox();

				if (!t)
					return;

				Rectanglef otherbbox = *t;

				if (otherbbox.top() >= bbox.bottom()) return;
				if (bbox.top() >= otherbbox.bottom()) return;

				// To the left
				if (bbox.right() <= otherbbox.left()) {
					float distance = otherbbox.left() - bbox.right();

					if (currentMotion > distance) {
						currentMotion = distance;
						collided = true;
					}
				}
				// To the right
				else if (bbox.left() >= otherbbox.right()) {
					float distance = bbox.left() - otherbbox.right();

					if (currentMotion < -distance) {
						currentMotion = -distance;
						collided = true;
					}
				}

				// Colliding
				else {
					return;
				}
			});

			if (collided)
				velocity.x = 0;
			position.x += currentMotion;
		}

		// Y motion
		{
			float currentMotion = velocity.y * state.context.deltaTime;
			bool collided = false;

			Rectanglef bbox = *getBoundingBox();

			m_Scene->forEach<EntityWall>([&](EntityWall &wall) {
				auto t = wall.getBoundingBox();

				if (!t)
					return;

				Rectanglef otherbbox = *t;

				if (otherbbox.left() >= bbox.right()) return;
				if (bbox.left() >= otherbbox.right()) return;

				// To the left
				if (bbox.bottom() <= otherbbox.top()) {
					float distance = otherbbox.top() - bbox.bottom();

					if (currentMotion > distance) {
						currentMotion = distance;
						collided = true;
					}
				}
				// To the right
				else if (bbox.top() >= otherbbox.bottom()) {
					float distance = bbox.top() - otherbbox.bottom();

					if (currentMotion < -distance) {
						currentMotion = -distance;
						collided = true;
					}
				}

				// Colliding
				else {
					return;
				}
			});

			if (velocity.y > 0 && collided) grounded = true;
			else grounded = false;


			if (collided)
				velocity.y = 0;

			position.y += currentMotion;
		}
	}

	void EntityPlayer::updateJump()
	{
		auto state = getState();

		// Update the jumphops
		if (state.input.isKeyPressed(KEY_SPACE))
			jumpHop = true;
		if (!state.input.isKeyDown(KEY_SPACE))
			jumpHop = false;

		if (jumpHop && grounded) {
			velocity.y = -2.85 * 60; // -2.73 in game maker?
			jumped = true;
			jumpHop = false;
		}

		if (velocity.y > 0)
			jumped = false;

		// Clip motion
		if (!state.input.isKeyDown(KEY_SPACE) && jumped) {
			velocity.y = 0;
		}
	}

	void EntityPlayer::updateMove() {
		auto state = getState();

		velocity.x = 0;

		if (state.input.isKeyDown(KEY_LEFT)) {
			velocity.x = -movementSpeed;
			drawScale.x = -1;
		}
		if (state.input.isKeyDown(KEY_RIGHT)) {
			velocity.x = movementSpeed;
			drawScale.x = 1;
		}
	}

	void EntityPlayer::updateAnimation()
	{
		controller.setValue("hspeed", velocity.x);
		controller.setValue("vspeed", velocity.y);
		controller.setValue("grounded", grounded);
		controller.update(getState().context.deltaTime);
	}
}
