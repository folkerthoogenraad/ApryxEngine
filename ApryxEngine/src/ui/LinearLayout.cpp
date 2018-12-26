#include "LinearLayout.h"

namespace apryx {

	void LinearLayout::updateLayout(Rectanglef newSize)
	{
		// TODO implement Exact scaling.
		UIComponent::updateLayout(newSize);

		if (getChildCount() == 0)
			return;

		Rectanglef rect = getLocalBounds();
		
		float weightSum = 0;
		float sizeSum = 0;
		
		// Calculate the weightSum and sizeSum
		for (int i = 0; i < getChildCount(); i++) {
			auto child = getChild(i);
			Size prefSize = child->getPreferredSize();
			
			if (m_Direction == Horizontal) {
				if (child->getLayoutParams().m_WidthScaling == LayoutParams::MatchParent) {
					weightSum += child->getLayoutParams().m_Weight.x;
				}
				else {
					sizeSum += prefSize.x;
				}
			}
			if (m_Direction == Vertical) {
				if (child->getLayoutParams().m_HeightScaling == LayoutParams::MatchParent) {
					weightSum += child->getLayoutParams().m_Weight.y;
				}
				else {
					sizeSum += prefSize.y;
				}
			}
		}

		// Calculate how much size 1 'weight' is worth
		float sizePerWeight = 1.0;

		if(m_Direction == Horizontal){
			sizePerWeight = (rect.width() - sizeSum - (getChildCount() - 1) * m_Gap) / weightSum;
		}
		else {
			sizePerWeight = (rect.width() - sizeSum - (getChildCount() - 1) * m_Gap) / weightSum;
		}

		// Current position for the layout
		Vector2f position;

		// Actually do the layouting
		for (int i = 0; i < getChildCount(); i++) {
			auto child = getChild(i);
			Size prefSize = child->getPreferredSize();
			const LayoutParams &params = child->getLayoutParams();
			
			if(m_Direction == Horizontal){
				Size size = prefSize;

				if (params.m_WidthScaling == LayoutParams::MatchParent) {
					size.width = sizePerWeight * params.m_Weight.x;
				}

				if (params.m_HeightScaling == LayoutParams::MatchParent) {
					size.height = rect.height();
				}

				child->updateLayout(Rectanglef(position, size));
				position.x += m_Gap + size.x;
			}
		}
	}

	void LinearLayout::init(ApryxUI *ui)
	{
		UIComponent::init(ui);

		for (auto &c : m_Children) {
			c->init(ui);
		}
	}

	void LinearLayout::update()
	{
		for (auto &c : m_Children) {
			c->update();
		}
	}

	void LinearLayout::draw(Graphics2D & graphics)
	{
		for (auto &c : m_Children) {
			c->draw(graphics);
		}
	}


	void LinearLayout::addComponent(std::shared_ptr<UIComponent> component)
	{
		m_Children.push_back(component);
	}
}
