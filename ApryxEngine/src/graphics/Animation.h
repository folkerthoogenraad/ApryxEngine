#pragma once

#include <vector>

#include "Sprite.h"


namespace apryx {

	class Animation {
		std::vector<Sprite> m_Sprites;
		float m_Index;

		float m_Speed; // Images per second
	public:
		void update(float delta);
		void restart();

		float getSpeed() const { return m_Speed; }
		void setSpeed(float speed) {m_Speed = speed; }

		const Sprite &getCurrentSprite() const;

		void addSprite(Sprite sprite);
	};

}