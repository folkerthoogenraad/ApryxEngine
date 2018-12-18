#include "EntityComponentSystem.h"

namespace apryx{
	ComponentList::ComponentList(ComponentList && c)
		:
		size(c.size), 
		reserved(c.reserved),
		components(c.components)
#ifdef _DEBUG
		, componentIndex(c.componentIndex)
#endif
	{
		c.components = nullptr;
	}
	ComponentList::~ComponentList(){
        delete[] components;
    }
    
    Entity EntityComponentSystem::createEntity()
    {
        Entity en;

        en.id = currentId++;

        entities.push_back(en);

        return en;
    }

}