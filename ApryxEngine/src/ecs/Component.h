#pragma once

namespace apryx{

	// Kinda sad that this has to exist. I think we can do without it if we use Component<T> as a template
	// TODO think about the component and create a way to create components from arbatrary things

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