#include "EntityPlayer.h"

#include "math/math.h"

namespace apryx {
	void EntityPlayer::init(Scene * scene)
	{
		sprite = Sprite(scene->getContext()->loadTexture("Player.png"));
		sprite.setCenter();

		position.x = 40;
		position.y = 40;
	}

	void EntityPlayer::update()
	{
		Context &context = *m_Scene->getContext();
		InputManager &input = m_Scene->getContext()->input;

		previousPosition = position;

		velocity.y += gravity * context.deltaTime;

		velocity.x = 0;

		if (input.isKeyDown(KEY_LEFT)) {
			velocity.x = -movementSpeed;
			drawScale.x = -1;
		}
		if (input.isKeyDown(KEY_RIGHT)) {
			velocity.x = movementSpeed;
			drawScale.x = 1;
		}
		if (input.isKeyPressed(KEY_SPACE)) {
			velocity.y = -7 * 60;
		}

		position += velocity * context.deltaTime;

		if (position.y < 32) {
			position.y = 32;
			velocity.y = 0;
		}
		if (position.y > 100) {
			position.y = 100;
			velocity.y = 0;
		}
	}

	void EntityPlayer::draw(Graphics2D & graphics)
	{
		Context &context = *m_Scene->getContext();
		graphics.drawSprite(Paint(Color32::white()), sprite, lerp(previousPosition, position, context.frameTime), drawScale);
	}
}
