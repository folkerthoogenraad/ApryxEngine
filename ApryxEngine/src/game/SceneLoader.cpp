#include "SceneLoader.h"

namespace apryx {

	std::vector<std::shared_ptr<Entity2D>> SceneLoader::loadFile(const std::string & file)
	{
		return std::vector<std::shared_ptr<Entity2D>>();
	}

	void SceneLoader::registerLoader(const std::string & name, EntityLoader loader)
	{
		m_Loaders.insert_or_assign(name, loader);
	}

	void SceneLoader::unregisterLoader(const std::string & name)
	{
		m_Loaders.erase(name);
	}

}
