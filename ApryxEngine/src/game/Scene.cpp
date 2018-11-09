#include "Scene.h"

#include "Entity.h"

#include <assert.h>


namespace apryx {

	void Scene2D::init(std::shared_ptr<Context> context)
	{
		assert(context != nullptr);
		m_Context = context;
	}

	void Scene2D::update()
	{
		for (auto &entity : m_Entities) {
			entity->update();
		}
	}

	void Scene2D::draw(Graphics2D & graphics)
	{
		for (auto &entity : m_Entities) {
			entity->draw(graphics);
		}
	}

	void Scene2D::addEntity(std::shared_ptr<Entity2D> entity)
	{
		entity->setScene(this);
		entity->init(this);
		m_Entities.push_back(std::move(entity));
	}
}
