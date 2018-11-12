#pragma once

#include "ApryxUI.h"

#include "math/Rectangle.h"

namespace apryx {

	struct Insets {
		int top, right, bottom, left;

		Insets() = default;
		Insets(int a, int b, int c, int d) : top(a), right(b), bottom(c), left(d) {}

		static Insets defaultInsets() { return Insets(2, 2, 2, 2); }
		static Insets none() { return Insets(0, 0, 0, 0); }
	};

	class ApryxUI;

	class Component {
		ApryxUI *m_UI;
		Component *m_Parent;

		Rectanglef m_LayoutBounds;
		Insets m_Insets = Insets::defaultInsets();

		std::string m_ID = "";
	public:
		virtual void init() { }
		virtual void update() {}
		virtual void draw(Graphics2D &graphics) {}

		Rectanglef getLayoutBounds() { return m_LayoutBounds; }
		Rectanglef getLocalBounds();

		virtual void updateLayout(Rectanglef newSize) { m_LayoutBounds = newSize; }

		const std::string &getID() const { return m_ID; }
		void setID(std::string id) { m_ID = std::move(id); }

		virtual int getChildCount() const { return 0; }
		virtual const Component *getChild(int index) const { return nullptr; }

		void setParent(Component *component) { m_Parent = component; }
		Component *getParent() { return m_Parent; }

		ApryxUI *getUI() { return m_UI; }
		void setUI(ApryxUI *ui) { m_UI = ui; }

		
	};

}