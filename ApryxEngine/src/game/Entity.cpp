#include "Entity.h"

#include "math/math.h"

namespace apryx {
	void Entity2D::preUpdate()
	{
		previousPosition = position;
	}

	EntityState Entity2D::getState()
	{
		return EntityState
		{
			*m_Scene,
			*m_Scene->getContext(),
			m_Scene->getContext()->input,
		};
	}

	Vector2f apryx::Entity2D::getDrawPosition() const {
		return m_Scene == nullptr ?
			position :
			lerp(previousPosition, position, m_Scene->getContext()->frameTime);
	}
}
