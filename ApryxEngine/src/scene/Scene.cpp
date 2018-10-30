#include "Scene.h"

#include "Entity.h"

#include <assert.h>


namespace apryx {

	void Scene::init(std::shared_ptr<Context> context)
	{
		assert(context != nullptr);
		m_Context = context;
	}

	void Scene::update()
	{
		for (auto &entity : m_Entities) {
			entity->update();
		}
	}

	void Scene::draw(Graphics2D & graphics)
	{
		for (auto &entity : m_Entities) {
			entity->draw(graphics);
		}
	}

	void Scene::addEntity(std::shared_ptr<Entity> entity)
	{
		entity->setScene(this);
		entity->init(this);
		m_Entities.push_back(std::move(entity));
	}
}
