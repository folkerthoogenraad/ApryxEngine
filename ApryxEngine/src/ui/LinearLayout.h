#pragma once

#include "UIComponent.h"

#include <memory>
#include <vector>

namespace apryx {
	
	class LinearLayout : public UIComponent {
	public:
		enum Direction {
			Horizontal,
			Vertical
		};
	private:
		Direction m_Direction;
		std::vector<std::shared_ptr<UIComponent>> m_Children;
		float m_Gap = 0;
	public:
		LinearLayout(Direction direction) : m_Direction(direction) {}

		virtual void updateLayout(Rectanglef newSize);

		virtual void init(ApryxUI *ui) override;

		virtual void update() override;
		virtual void draw(Graphics2D &graphics) override;

		void addComponent(std::shared_ptr<UIComponent> component);

		void setGap(float gap) { m_Gap = gap; }
		float getGap() const { return m_Gap; }

		virtual int getChildCount() const { return m_Children.size(); }
		virtual const UIComponent *getChild(int index) const { return m_Children[index].get(); }
		virtual UIComponent *getChild(int index) { return m_Children[index].get(); }

	};

}