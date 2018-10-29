#include "Win32Window.h"

#include <Windowsx.h>

#include <iostream>
#include "opengl/GL.h"

#include "log/Log.h"

#define CLASS_NAME "ApryxWindowClass"

namespace apryx {


	static LRESULT CALLBACK DefaultWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Win32Window *p = ((Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA));

		if (p) {
			return p->handleWindowsMessage(uMsg, wParam, lParam);
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	static inline PIXELFORMATDESCRIPTOR win32GetPixelFormatDescriptor()
	{
		static  PIXELFORMATDESCRIPTOR pfd =              // pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),              // Size Of This Pixel Format Descriptor
			1,                                          // Version Number
			PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
			PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
			PFD_DOUBLEBUFFER,                           // Must Support Double Buffering
			PFD_TYPE_RGBA,                              // Request An RGBA Format
			32,                                         // Select Our Color Depth
			0, 0, 0, 0, 0, 0,                           // Color Bits Ignored
			0,                                          // No Alpha Buffer
			0,                                          // Shift Bit Ignored
			0,                                          // No Accumulation Buffer
			0, 0, 0, 0,                                 // Accumulation Bits Ignored
			24,                                         // 16Bit Z-Buffer (Depth Buffer)  
			8,                                          // No Stencil Buffer
			0,                                          // No Auxiliary Buffer
			PFD_MAIN_PLANE,                             // Main Drawing Layer
			0,                                          // Reserved
			0, 0, 0                                     // Layer Masks Ignored
		};

		return pfd;
	}

	static void registerClass()
	{
		WNDCLASS wc = {};

		wc.lpfnWndProc = DefaultWindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = CLASS_NAME;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);          // Load The Default Icon
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // Load The Arrow Pointer


		RegisterClass(&wc);

	}

	static void initGL()
	{
		glewInit();

		glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glClearColor(0, 0, 1, 1);
	}

	Win32Window::Win32Window(std::string title, int width, int height, bool full)
		: Window(title, width, height, false)
	{
		m_Width = width;
		m_Height = height;

		SetProcessDPIAware();

		registerClass();

		// Make sure its the client size
		RECT wr = { 0, 0, width, height };    // set the size, but not the position
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size
		RegisterTouchWindow(m_Hwnd, 0);


		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;                    // Windows Style

		m_Hwnd = CreateWindowEx(
			dwExStyle,                              // Optional window styles.
			CLASS_NAME,								// Window class
			m_Title.c_str(),						// Window text
			dwStyle,								// Window style

			0, 0, wr.right - wr.left, wr.bottom - wr.top, // Size and position

			NULL,       // Parent window    
			NULL,       // Menu
			GetModuleHandle(NULL),  // Instance handle
			NULL        // Additional application data
		);


		if (!m_Hwnd) {
			MessageBox(NULL, "Failed to create window.", "Error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		// Set the user data
		SetWindowLongPtr(m_Hwnd, GWLP_USERDATA, (LONG_PTR)this);

		PIXELFORMATDESCRIPTOR descriptor = win32GetPixelFormatDescriptor();

		int pixelFormat;

		m_DeviceContext = GetDC(m_Hwnd);

		if (!m_DeviceContext) {
			MessageBox(NULL, "Failed to obtain the device context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;                               // Return FALSE
		}

		// Get the device scaling stuff
		m_DPIScale = GetDeviceCaps(m_DeviceContext, LOGPIXELSX) / 96.f;

		pixelFormat = ChoosePixelFormat(m_DeviceContext, &descriptor);

		if (!pixelFormat)
		{
			MessageBox(NULL, "Failed to find a correct pixel format.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		if (!SetPixelFormat(m_DeviceContext, pixelFormat, &descriptor))
		{
			MessageBox(NULL, "Failed to set the pixel format.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		m_GLContext = wglCreateContext(m_DeviceContext);

		if (!m_GLContext)
		{
			MessageBox(NULL, "Failed to create OpenGL context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		if (!wglMakeCurrent(m_DeviceContext, m_GLContext))
		{
			MessageBox(NULL, "Failed to make OpenGL context active on this thread.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		if (full) {
			setFullscreen(true);
		}

		initGL();
	}

	Win32Window::~Win32Window()
	{
		if (m_Fullscreen) {
			ChangeDisplaySettings(NULL, 0);
		}
		if (m_GLContext) {
			if (!wglMakeCurrent(NULL, NULL)) {
				Debug::logError("Failed to reset context");
			}
			if (!wglDeleteContext(m_GLContext))
			{
				Debug::logError("Failed to delete context");
			}
		}

		if (m_DeviceContext) {
			ReleaseDC(m_Hwnd, m_DeviceContext);
		}

		if (m_Hwnd) {
			if(!DestroyWindow(m_Hwnd)){
				Debug::logError("Failed to destroy window");
			}
		}
	}

	void Win32Window::setVisible(bool f)
	{
		setVisible(f, false);
	}

	void Win32Window::setVisible(bool visible, bool maximize)
	{
		m_Visible = visible;

		if (maximize && visible) {
			ShowWindow(m_Hwnd, SW_MAXIMIZE);
		}
		else if (visible) {
			ShowWindow(m_Hwnd, SW_SHOW);
		}
		else if (!visible) {
			ShowWindow(m_Hwnd, SW_HIDE);
		}
	}

	void Win32Window::setFullscreen(bool f)
	{
		if (f == m_Fullscreen)
			return;

		if (f) {
			// Save info
			m_Maximized = IsZoomed(m_Hwnd);

			if(m_Maximized)
				SendMessage(m_Hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);

			RECT r; GetWindowRect(m_Hwnd, &r);

			m_PreviousPosition = Rectanglei(r.left, r.top, r.right - r.left, r.bottom - r.top);

			// Enable fullscreen
			SetWindowLong(m_Hwnd, GWL_STYLE,
				dwStyle & ~(WS_CAPTION | WS_THICKFRAME));
			SetWindowLong(m_Hwnd, GWL_EXSTYLE,
				dwExStyle & ~(WS_EX_DLGMODALFRAME |
					WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

			MONITORINFO monitorInfo;
			monitorInfo.cbSize = sizeof(monitorInfo);
			GetMonitorInfo(MonitorFromWindow(m_Hwnd, MONITOR_DEFAULTTONEAREST), &monitorInfo);

			SetWindowPos(m_Hwnd, NULL, monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
				monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

			m_Width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
			m_Height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

			m_Fullscreen = true;

			setVisible(true);
		}
		else {
			SetWindowLong(m_Hwnd, GWL_STYLE, dwStyle);
			SetWindowLong(m_Hwnd, GWL_EXSTYLE, dwExStyle);

			
			SetWindowPos(m_Hwnd, NULL, m_PreviousPosition.x(), m_PreviousPosition.y(), m_PreviousPosition.width(), m_PreviousPosition.height(),
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
			
			m_Width = m_PreviousPosition.width();
			m_Height = m_PreviousPosition.height();

			m_Fullscreen = false;
			setVisible(true);

			if (m_Maximized)
				SendMessage(m_Hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

		}
	}

	bool Win32Window::isResized() const
	{
		return m_Resized;
	}

	bool Win32Window::isCloseRequested() const
	{
		return m_CloseRequested;
	}

	float Win32Window::getWidth() const
	{
		return m_Width / m_DPIScale;
	}

	float Win32Window::getHeight() const
	{
		return m_Height / m_DPIScale;
	}

	LRESULT Win32Window::handleWindowsMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_POINTERDOWN:
		{
			//https://msdn.microsoft.com/en-us/library/hh454928(v=vs.85).aspx


			POINT point;
			point.x = GET_X_LPARAM(lParam);
			point.y = GET_Y_LPARAM(lParam);

			ScreenToClient(m_Hwnd, &point);
		}
		break;

		case WM_CLOSE:
			m_CloseRequested = true;
			break;

		case WM_SIZE:
		{
			int width = LOWORD(lParam);  // Macro to get the low-order word. 
			int height = HIWORD(lParam); // Macro to get the high-order word. 

			m_Width = width;
			m_Height = height;

			m_Resized = true;
		}
		break;

		case WM_SYSCOMMAND:                     // Intercept System Commands
		{
			switch (wParam)                     // Check System Calls
			{
				case SC_SCREENSAVE:             // Screensaver Trying To Start?
				case SC_MONITORPOWER:               // Monitor Trying To Enter Powersave?
				return 0;                   // Prevent From Happening
			}
		}
		break;
		case WM_SYSKEYDOWN:
			if (wParam == VK_RETURN)
				if ((HIWORD(lParam) & KF_ALTDOWN))
					setFullscreen(!m_Fullscreen);

			if (wParam == VK_F4)
				if ((HIWORD(lParam) & KF_ALTDOWN))
					PostMessage(m_Hwnd, WM_CLOSE, 0, 0);
			return TRUE;

		case WM_SYSKEYUP:
			return TRUE;
		break;

		case WM_SYSCHAR:
			return TRUE;
		}

		return DefWindowProc(m_Hwnd, message, wParam, lParam);
	}

	void Win32Window::destroy()
	{
		wglDeleteContext(m_GLContext);
		CloseWindow(m_Hwnd);
	}

	float Win32Window::dpiScale() const
	{
		return m_DPIScale;
	}

	void Win32Window::poll()
	{
		m_CloseRequested = false;
		m_Resized = false;


		MSG msg = {};
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Win32Window::swap()
	{
		HDC dc = GetDC(m_Hwnd);
		SwapBuffers(dc);
		ReleaseDC(m_Hwnd, dc);
	}

}
