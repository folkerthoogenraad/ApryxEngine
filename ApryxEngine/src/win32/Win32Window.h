#pragma once

#include "graphics/Window.h"
#include "math/Rectangle.h"

#include <Windows.h>

#include <vector>

#include "input/InputEvent.h"

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

		std::vector<InputEvent> m_InputEvents;
	public:
		Win32Window(std::string title, int width, int height, bool full, bool vsync);
		~Win32Window();

		bool isResized() const override;
		bool isCloseRequested() const override;

		void setVisible(bool f) override;
		void setVisible(bool visible, bool maximize);

		void setFullscreen(bool f) override;
		void setVSync(bool f) override;

		bool getVSync() const { return m_VSync; }

		float getWidth() const override;
		float getHeight() const override;

		int getRawWidth() const override { return m_Width; }
		int getRawHeight() const override { return m_Height; }

		void destroy() override;
		float dpiScale() const override;

		const std::vector<InputEvent> &getWindowEvents() const { return m_InputEvents; };

		LRESULT handleWindowsMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		void poll();
		void swap();
	};
}