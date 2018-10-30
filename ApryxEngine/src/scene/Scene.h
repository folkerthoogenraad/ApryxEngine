#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "resources/Context.h"


namespace apryx {

	class Entity;

	class Scene {
		std::vector<std::shared_ptr<Entity>> m_Entities;
		std::shared_ptr<Context> m_Context;
	public:
		virtual void init(std::shared_ptr<Context> context);

		virtual void update();
		virtual void draw(Graphics2D &graphics);

		void addEntity(std::shared_ptr<Entity> entity);

		std::shared_ptr<Context> getContext() const { return m_Context; }

		template<typename T>
		void forEach(std::function<void(T &entity)> func) 
		{
			for (std::shared_ptr<Entity> &en : m_Entities) 
			{
				std::shared_ptr<T> entity = std::dynamic_pointer_cast<T>(en);
				if (entity != nullptr) {
					func(*entity);
				}
			}
		}
	};

}