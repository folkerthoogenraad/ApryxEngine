#pragma once

#include "graphics/Font.h"

#include "UIComponent.h"

#include <string>
#include <memory>

namespace apryx {

	class Button : public UIComponent {
	public:
		enum ButtonType {
			Primary,
			Secondary
		};
	private:
		std::string m_EditableText;
		std::shared_ptr<Font> m_Font;
		ButtonType m_Type;

		bool m_Pressed = false;
	public:
		Button(std::string text = "Sample Text", ButtonType type = ButtonType::Primary);

		virtual void init(ApryxUI *ui) override;

		virtual void draw(Graphics2D &graphics) override;

		virtual Size getPreferredSize() const  override;

		void setFont(std::shared_ptr<Font> font) { m_Font = font; }
		const std::shared_ptr<Font> &getFont() const { return m_Font; }
		
		void setText(std::string str) { m_EditableText = std::move(str); }
		const std::string &getText() const { return m_EditableText; }

		ButtonType getButtonType() const { return m_Type; }
		void setButtonType(ButtonType type) { m_Type = type; }

		virtual void onMousePressed(InputEvent event) override;
		virtual void onMouseReleased(InputEvent event) override;
		virtual void onMouseClick(InputEvent event) override;
	};

}