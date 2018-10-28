#pragma once

namespace apryx {

	class Graphics2D;

	class Entity {

		void update();
		void draw(Graphics2D &graphics);

	};

	class Player : public Entity{
		Sprite sprite;

		void update();
		void interpolate();
		void draw(Graphics2D &graphics);
	};

}