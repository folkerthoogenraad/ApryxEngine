#pragma once
#pragma once

#include "graphics/Font.h"

#include "UIComponent.h"

#include "EditableText.h"

namespace apryx {

	class TextField : public UIComponent {
	private:
		EditableText m_EditableText;
		std::string m_Hint;
		std::shared_ptr<Font> m_Font;

		bool m_Focussed = false;
	public:
		TextField(std::string hint = "Sample Text");

		virtual void init(ApryxUI *ui) override;

		virtual void draw(Graphics2D &graphics) override;

		virtual Size getPreferredSize() const override;

		void setFont(std::shared_ptr<Font> font) { m_Font = font; }
		const std::shared_ptr<Font> &getFont() const { return m_Font; }

		void setText(std::string str) { m_EditableText.setText(std::move(str)); }
		const std::string &getText() const { return m_EditableText.getText(); }

		virtual void onKeyTyped(InputEvent event) override;
		virtual void onKeyPressed(InputEvent event) override;

		virtual void onMousePressed(InputEvent event) override;
		virtual void onMouseDrag(InputEvent event) override;
		virtual void onMouseReleased(InputEvent event) override;

		virtual void onFocusGain(InputEvent event) override;
		virtual void onFocusLose(InputEvent event) override;

		virtual int positionToIndex(Vector2f pos);
	};

}