#include "Component.h"

namespace apryx {
	
	Rectanglef apryx::Component::getLocalBounds()
	{
		Rectanglef rectangle = getLayoutBounds();

		rectangle.position.x += m_Insets.left;
		rectangle.position.y += m_Insets.top;
		rectangle.size.x -= m_Insets.left + m_Insets.right;
		rectangle.size.y -= m_Insets.bottom + m_Insets.top;

		return std::move(rectangle);
	}

}
