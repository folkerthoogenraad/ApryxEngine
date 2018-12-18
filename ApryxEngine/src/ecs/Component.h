#pragma once

namespace apryx{

    struct Component{
		int entityId;
		virtual ~Component() {}
    };

	size_t generateComponentId();

    template<typename T>
    size_t getComponentId()
    {
        static size_t id = generateComponentId();
        return id;
    }

}