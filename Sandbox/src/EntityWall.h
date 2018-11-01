#pragma once

#include "scene/Entity.h"

namespace apryx {

	class EntityWall : public Entity {
	public:
		virtual void init(Scene *m_Scene) override;
		virtual void update() override;
		virtual void draw(Graphics2D &graphics) override;
		
		virtual std::optional<Rectanglef> getBoundingBox() const override;
	};

}