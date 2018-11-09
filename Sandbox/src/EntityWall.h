#pragma once

#include "game/Entity.h"

namespace apryx {

	class EntityWall : public Entity2D {
	public:
		virtual void init(Scene2D *m_Scene) override;
		virtual void update() override;
		virtual void draw(Graphics2D &graphics) override;
		
		virtual std::optional<Rectanglef> getBoundingBox() const override;
	};

}