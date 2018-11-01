#include "EntityWall.h"

namespace apryx {

	void EntityWall::init(Scene * m_Scene)
	{
	}

	void EntityWall::update()
	{
	}

	void EntityWall::draw(Graphics2D & graphics)
	{
		graphics.drawRectangle(Paint(Color32::red()), *getBoundingBox());
	}

	std::optional<Rectanglef> EntityWall::getBoundingBox() const
	{
		return Rectanglef(position, Vector2f(16,16));
	}
}
