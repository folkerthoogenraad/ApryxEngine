#include "ApryxUI.h"

#include "UIComponent.h"

namespace apryx {

	void apryx::ApryxUI::update()
	{
		if (m_MainComponent == nullptr)
			return;

		m_MainComponent->update();
	}

	void ApryxUI::draw(Graphics2D & graphics)
	{
		if (m_MainComponent == nullptr)
			return;

		m_MainComponent->draw(graphics);
	}

	void ApryxUI::updateLayout(float width, float height) {
		if (m_MainComponent != nullptr) {
			m_MainComponent->updateLayout(Rectanglef(0, 0, width, height));
		}
	}

	void ApryxUI::setMainComponent(std::shared_ptr<UIComponent> component)
	{
		// TODO update the layout for the main component.
		m_MainComponent = component;

		component->setUI(this);
		component->init();
		
	}

}
