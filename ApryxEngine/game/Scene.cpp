#include "Scene.h"

#include <assert.h>

namespace apryx {
	Scene::Scene(std::shared_ptr<ResourceManager> manager)
		: m_Manager(manager)
	{
		assert(manager != nullptr);
	}
	void Scene::addEntity(std::shared_ptr<Entity> entity)
	{
		entity->setScene(this);
		m_Entities.push_back(std::move(entity));
	}
}
