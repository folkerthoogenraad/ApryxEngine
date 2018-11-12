#include "LinearLayout.h"

namespace apryx {

	void LinearLayout::updateLayout(Rectanglef newSize)
	{
		Component::updateLayout(newSize);

		Rectanglef rect = getLocalBounds();
		
		Vector2f position;

		for (int i = 0; i < getChildCount(); i++) {
			auto child = getChild(i);
			Size prefSize = child->getPreferredSize();
			
			if(m_Direction == Horizontal){
				child->updateLayout(Rectanglef(position, prefSize));
				position.x += m_Gap + prefSize.x;
			}
		}
	}

	void LinearLayout::init()
	{
		for (auto &c : m_Children) {
			c->setUI(getUI());
			c->init();
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


	void LinearLayout::addComponent(std::shared_ptr<Component> component)
	{
		m_Children.push_back(component);
	}
}
