#pragma once

#include "Component.h"

#include <memory>
#include <vector>

namespace apryx {
	
	class LinearLayout : public Component{
	public:
		enum Direction {
			Horizontal,
			Vertical
		};
	private:
		Direction m_Direction;
		std::vector<std::shared_ptr<Component>> m_Children;
		float m_Gap = 0;
	public:
		LinearLayout(Direction direction) : m_Direction(direction) {}

		virtual void updateLayout(Rectanglef newSize);

		virtual void init() override;

		virtual void update() override;
		virtual void draw(Graphics2D &graphics) override;
	
		void addComponent(std::shared_ptr<Component> component);

		virtual int getChildCount() const { return m_Children.size(); }
		virtual const Component *getChild(int index) const { return m_Children[index].get(); }
		virtual Component *getChild(int index) { return m_Children[index].get(); }

	};

}