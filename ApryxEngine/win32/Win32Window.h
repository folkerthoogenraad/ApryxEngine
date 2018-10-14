#pragma once

#include "graphics/Window.h"

#include <Windows.h>

namespace apryx {
	class Win32Window : public Window {
		HWND m_Hwnd;

		HGLRC m_GLContext;

		bool m_CloseRequested;
		bool m_Resized;

		float m_DPIScale = 1;
	public:
		Win32Window(std::string title, int width, int height, bool full);

		bool isResized() const override;
		bool isCloseRequested() const override;

		void setVisible(bool f) override;
		void setVisible(bool visible, bool maximize);

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