#pragma once

#include <map>
#include <string>
#include <memory>
#include <functional>

namespace apryx {

	class Entity2D;

	using EntityLoader = std::function<std::shared_ptr<Entity2D>()>;

	class SceneLoader {
		std::map<std::string, EntityLoader> m_Loaders;
	public:

		std::vector<std::shared_ptr<Entity2D>> loadFile(const std::string &file);

		void registerLoader(const std::string &name, EntityLoader loader);
		void unregisterLoader(const std::string &name);
	};

}