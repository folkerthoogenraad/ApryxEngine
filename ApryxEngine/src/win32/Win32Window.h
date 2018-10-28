#pragma once

#include "graphics/Window.h"
#include "math/Rectangle.h"

#include <Windows.h>

namespace apryx {
	class Win32Window : public Window {
		HWND m_Hwnd;
		HDC m_DeviceContext;

		DWORD dwExStyle = 0;
		DWORD dwStyle = 0;

		Rectanglei m_PreviousPosition;
		bool m_Maximized = false;
		bool m_Visible = false;

		HGLRC m_GLContext;

		bool m_CloseRequested = false;
		bool m_Resized = false;

		float m_DPIScale = 1;
	public:
		Win32Window(std::string title, int width, int height, bool full);
		~Win32Window();

		bool isResized() const override;
		bool isCloseRequested() const override;

		void setVisible(bool f) override;
		void setVisible(bool visible, bool maximize);

		void setFullscreen(bool f);

		float getWidth() const override;
		float getHeight() const override;

		int getRawWidth() const { return m_Width; }
		int getRawHeight() const { return m_Height; }

		void destroy() override;
		float dpiScale() const override;

		LRESULT handleWindowsMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		void poll();
		void swap();
	};
}