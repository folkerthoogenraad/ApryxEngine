#pragma once

#include <vector>
#include <memory>

#include "Entity.h"
#include "resources/ResourceManager.h"

namespace apryx {

	class Scene {
		std::vector<std::shared_ptr<Entity>> m_Entities;
		std::shared_ptr<ResourceManager> m_Manager;
	public:
		Scene(std::shared_ptr<ResourceManager> manager);

		void addEntity(std::shared_ptr<Entity> entity);

		std::shared_ptr<ResourceManager> getResourceManager() const { return m_Manager; }
	};

}