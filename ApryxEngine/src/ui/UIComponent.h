#pragma once

#include "ApryxUI.h"
#include "LayoutParams.h"

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

	using Size = Vector2f;

	class UIComponent {
		ApryxUI *m_UI = nullptr;
		UIComponent *m_Parent = nullptr;

		Rectanglef m_LayoutBounds;
		Insets m_Insets = Insets::defaultInsets();
		LayoutParams m_LayoutParams;

		std::string m_ID = "";
	public:
		virtual void init() { }
		virtual void update() {}
		virtual void draw(Graphics2D &graphics) {}

		void requestLayoutUpdate() { if (m_Parent != nullptr) m_Parent->requestLayoutUpdate(); else updateLayout(getLayoutBounds()); }

		Rectanglef getLayoutBounds() { return m_LayoutBounds; }
		Rectanglef getLocalBounds();

		virtual void updateLayout(Rectanglef newSize) { m_LayoutBounds = newSize; }

		virtual Size getPreferredSize() const { return Size(16, 16); };

		const std::string &getID() const { return m_ID; }
		void setID(std::string id) { m_ID = std::move(id); }

		virtual int getChildCount() const { return 0; }
		virtual const UIComponent *getChild(int index) const { return nullptr; }
		virtual UIComponent *getChild(int index) { return nullptr; }

		void setParent(UIComponent *component) { m_Parent = component; }
		UIComponent *getParent() { return m_Parent; }

		ApryxUI *getUI() { return m_UI; }
		void setUI(ApryxUI *ui) { m_UI = ui; }

		// Update the layout parameters and update the new layout
		void setLayoutParams(LayoutParams newParams) { m_LayoutParams = newParams; requestLayoutUpdate(); }

		// Update the layout paramters without changing the actual layout (use with care)
		void setLayoutParamsRaw(LayoutParams newParams) { m_LayoutParams = newParams; }

		// Returns the layout parameters for this component
		const LayoutParams &getLayoutParams() const { return m_LayoutParams; }
	};

}