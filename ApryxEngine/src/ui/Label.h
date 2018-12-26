#pragma once

#include "graphics/Font.h"

#include "UIComponent.h"

#include <string>
#include <memory>

namespace apryx {

	class Label : public UIComponent {
	private:
		std::string m_EditableText;
		std::shared_ptr<Font> m_Font;
	public:
		Label(std::string text = "Sample Text");

		virtual void init(ApryxUI *ui) override;

		virtual void draw(Graphics2D &graphics) override;

		virtual Size getPreferredSize() const  override;

		void setFont(std::shared_ptr<Font> font) { m_Font = font; }
		const std::shared_ptr<Font> &getFont() const { return m_Font; }

		void setText(std::string str) { m_EditableText = std::move(str); }
		const std::string &getText() const { return m_EditableText; }
	};

}