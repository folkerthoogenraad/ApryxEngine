#pragma once

#include <vector>
#include <memory>

#include "resources/ResourceManager.h"

namespace apryx {

	class Entity;

	class Scene {
		std::vector<std::shared_ptr<Entity>> m_Entities;
		std::shared_ptr<ResourceManager> m_Manager;
	public:
		Scene(std::shared_ptr<ResourceManager> manager);

		virtual void update();
		virtual void draw(Graphics2D &graphics);

		void addEntity(std::shared_ptr<Entity> entity);

		std::shared_ptr<ResourceManager> getResourceManager() const { return m_Manager; }
	};

}