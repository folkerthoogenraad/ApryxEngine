#pragma once
#include <string>

namespace apryx {

	class Window {
	protected:
		int m_Width;
		int m_Height;
		bool m_Fullscreen;
		std::string m_Title;

	public:
		Window(std::string title, int width = 640, int height = 480, bool full = false) : m_Title(title), m_Width(width), m_Height(height), m_Fullscreen(full) {};
		
		virtual void destroy() = 0;

		virtual bool isCloseRequested() const = 0;
		virtual bool isResized() const = 0;

		virtual float dpiScale() const { return 1; }

		virtual float getWidth() const = 0;
		virtual float getHeight() const = 0;

		virtual void setVisible(bool f) = 0;
		
		// Poll should return event queue
		virtual void poll() = 0;
		virtual void swap() = 0;

	};

}