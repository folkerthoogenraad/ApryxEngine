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
		graphics.drawClear(Color32::white());

		// Don't redraw again
		m_Redraw = false;

		if (m_MainComponent == nullptr)
			return;

		m_MainComponent->draw(graphics);
	}

	void ApryxUI::updateLayout(float width, float height) {
		if (m_MainComponent != nullptr) {
			m_MainComponent->updateLayout(Rectanglef(0, 0, width, height));
		}
	}

	void ApryxUI::processEvents(const std::vector<InputEvent>& events)
	{
		update();

		for (auto event : events) {
			switch (event.getType()) {

			case InputEvent::WindowResize:
			{
				updateLayout(event.m_WindowSize.width, event.m_WindowSize.height);
				redraw();
				break;
			}

			case InputEvent::KeyboardPressed:
			{
				if (auto ptr = m_FocusComponent.lock()) {
					ptr->onKeyPressed(event);
				}
				break;
			}
			case InputEvent::KeyboardReleased:
			{
				if (auto ptr = m_FocusComponent.lock()) {
					ptr->onKeyReleased(event);
				}
				break;
			}
			case InputEvent::KeyboardTyped:
			{
				if (auto ptr = m_FocusComponent.lock()) {
					ptr->onKeyTyped(event);
				}
				break;
			}

			case InputEvent::MouseMove:
			{
				m_MousePosition = event.getMousePosition();

				auto hover = getComponentAtPosition(m_MousePosition);
				auto oldHover = m_HoverComponent.lock();

				for (auto &c : m_PressedComponents) {
					if(c != nullptr)
						c->onMouseDrag(event);
				}

				if (hover != oldHover)
				{
					if (oldHover != nullptr)
						oldHover->onHoverEnd(event);

					if (hover != nullptr)
						hover->onHoverStart(event);

					// Update the new hover component
					m_HoverComponent = hover;
				}
				break;
			}
			case InputEvent::MousePressed:
			{
				if (auto hover = m_HoverComponent.lock()) {
					if (auto m = m_FocusComponent.lock()) {
						if (m != hover) {
							m->onFocusLose(event);
							hover->onFocusGain(event);
						}
					}
					else {
						hover->onFocusGain(event);
					}


					m_PressedComponents[event.getMouseButton()] = hover;
					m_PressedComponents[event.getMouseButton()]->onMousePressed(event);
					m_FocusComponent = hover;
				}
				break;
			}
			case InputEvent::MouseReleased:
			{
				if(m_PressedComponents[event.getMouseButton()]){
					auto hover = m_HoverComponent.lock();

					m_PressedComponents[event.getMouseButton()]->onMouseReleased(event);

					if (m_PressedComponents[event.getMouseButton()] == hover) {
						m_PressedComponents[event.getMouseButton()]->onMouseClick(event);
					}

					m_PressedComponents[event.getMouseButton()] = nullptr;
				}
				break;
			}
			}

		}
	}

	void ApryxUI::setMainComponent(std::shared_ptr<UIComponent> component)
	{
		// TODO update the layout for the main component.
		m_MainComponent = component;

		component->init(this);
		
	}

	std::shared_ptr<UIComponent> ApryxUI::getComponentAtPosition(Vector2f position)
	{
		if (m_MainComponent == nullptr)
			return nullptr;

		if(auto c = m_MainComponent->getComponentAtPosition(position)){
			return c;
		}

		return m_MainComponent;
	}

}
