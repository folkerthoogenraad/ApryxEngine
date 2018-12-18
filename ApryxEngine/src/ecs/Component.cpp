#include "Component.h"

namespace apryx {

	size_t generateComponentId() {
		static size_t id = 0;
		return id++;
	}

}