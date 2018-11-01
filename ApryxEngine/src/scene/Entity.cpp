#include "Entity.h"

#include "math/math.h"

namespace apryx {
	void Entity::preUpdate()
	{
		previousPosition = position;
	}

	EntityState Entity::getState()
	{
		return EntityState
		{
			*m_Scene,
			*m_Scene->getContext(),
			m_Scene->getContext()->input,
		};
	}

	Vector2f apryx::Entity::getDrawPosition() const {
		return m_Scene == nullptr ?
			position :
			lerp(previousPosition, position, m_Scene->getContext()->frameTime);
	}
}
