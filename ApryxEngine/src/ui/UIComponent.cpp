#include "UIComponent.h"

namespace apryx {
	
	Rectanglef apryx::UIComponent::getLocalBounds() const
	{
		Rectanglef rectangle = getLayoutBounds();

		rectangle.position.x += m_Insets.left;
		rectangle.position.y += m_Insets.top;
		rectangle.size.x -= m_Insets.left + m_Insets.right;
		rectangle.size.y -= m_Insets.bottom + m_Insets.top;

		return std::move(rectangle);
	}

	bool UIComponent::inBounds(Vector2f position) const
	{
		return getLocalBounds().contains(position);
	}

	std::shared_ptr<UIComponent> UIComponent::getComponentAtPosition(Vector2f position) const
	{
		for (int i = 0; i < getChildCount(); i++) {
			auto c = getChild(i);

			if (c->inBounds(position)) {
				auto childOf = c->getComponentAtPosition(position);

				if (childOf != nullptr)
					return childOf;
				else
					return c;
			}
		}

		return nullptr;
	}

	void UIComponent::redraw()
	{
		auto ui = getUI();

		if (ui != nullptr) {
			ui->redraw();
		}
	}

}
