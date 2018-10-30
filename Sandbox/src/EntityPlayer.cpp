#include "EntityPlayer.h"

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

		if (input.isKeyDown(KEY_LEFT)) {
			position.x -= 80 * context.deltaTime;
		}
		if (input.isKeyDown(KEY_RIGHT)) {
			position.x += 80 * context.deltaTime;
		}
	}

	void EntityPlayer::draw(Graphics2D & graphics)
	{
		graphics.drawSprite(Paint(Color32::white()), sprite, position);
	}
}
