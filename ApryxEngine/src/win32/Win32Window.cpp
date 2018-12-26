#include "Win32Window.h"

#include <Windowsx.h>

#include <iostream>
#include "opengl/GL.h"
#include "wglext.h"

#include "console/Console.h"

#include "input/InputEvent.h"

#include <vector>
#include <bitset>

#define CLASS_NAME "ApryxWindowClass"

namespace apryx {

	static bool WGLExtensionSupported(const char *extension_name)
	{
		// this is pointer to function which returns pointer to string with list of all wgl extensions
		PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;

		// determine pointer to wglGetExtensionsStringEXT function
		_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");

		if (strstr(_wglGetExtensionsStringEXT(), extension_name) == NULL)
		{
			// string was not found
			return false;
		}

		// extension is supported
		return true;
	}

	PFNWGLSWAPINTERVALEXTPROC       wglSwapIntervalEXT = NULL;
	PFNWGLGETSWAPINTERVALEXTPROC    wglGetSwapIntervalEXT = NULL;
	PFNWGLCHOOSEPIXELFORMATARBPROC	wglChoosePixelFormatARB = NULL;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

	static void InitWGL() {
		if ((wglSwapIntervalEXT == NULL || wglGetSwapIntervalEXT == NULL) && WGLExtensionSupported("WGL_EXT_swap_control"))
		{
			// Extension is supported, init pointers.
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

			// this is another function from WGL_EXT_swap_control extension
			wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
		}

		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
	}

	static bool IsRepeated(LPARAM lParam) {
		return HIWORD(lParam) & KF_REPEAT;
	}

	static WPARAM GetVirtualKey(WPARAM wParam, LPARAM lParam) 
	{
		UINT scancode = (lParam & 0x00ff0000) >> 16;
		bool extended = (lParam & 0x01000000) != 0;

		if (wParam == KEY_ANY_CONTROL)
		{
			if (extended) return KEY_RCONTROL;
			else return KEY_LCONTROL;
		}

		if (wParam == KEY_ANY_SHIFT)
		{
			return MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
		}

		if (wParam == KEY_ANY_ALT)
		{
			return MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
		}

		return wParam;
	}

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
		glewExperimental = true;
		glewInit();

		glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glClearColor(0, 0, 1, 1);

		checkGLError();
	}

	Win32Window::Win32Window(std::string title, int width, int height, bool full, bool vsync)
		: Window(title, width, height, false, false)
	{
		m_Width = width;
		m_Height = height;
		
		SetProcessDPIAware();

		registerClass();

		// Make sure its the client size
		RECT wr = { 0, 0, width, height };    // set the size, but not the position
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;

		// ===========================================================//
		// CREATE FAKE WINDOW TO INIT WGL
		// ===========================================================//
		HWND fakeWindow = CreateWindowEx(
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

		if (!fakeWindow) {
			MessageBox(NULL, "Failed to create window.", "Error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		HDC fakeDeviceContext = GetDC(fakeWindow);

		if (!fakeDeviceContext) {
			MessageBox(NULL, "Failed to obtain the device context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;                               // Return FALSE
		}

		// Get the device scaling stuff
		m_DPIScale = GetDeviceCaps(fakeDeviceContext, LOGPIXELSX) / 96.f;

		PIXELFORMATDESCRIPTOR descriptor = win32GetPixelFormatDescriptor();

		int fakePixelFormat = ChoosePixelFormat(fakeDeviceContext, &descriptor);

		if (!fakePixelFormat)
		{
			MessageBox(NULL, "Failed to find a correct pixel format.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		if (!SetPixelFormat(fakeDeviceContext, fakePixelFormat, &descriptor))
		{
			MessageBox(NULL, "Failed to set the pixel format.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		HGLRC fakeGLContext = wglCreateContext(fakeDeviceContext);
		if (!fakeGLContext)
		{
			MessageBox(NULL, "Failed to create OpenGL context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		if (!wglMakeCurrent(fakeDeviceContext, fakeGLContext))
		{
			MessageBox(NULL, "Failed to make OpenGL context active on this thread.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		InitWGL();

		// ===========================================================//
		// Create actual window
		// ===========================================================//
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
		
		SetWindowLongPtr(m_Hwnd, GWLP_USERDATA, (LONG_PTR)this);

		m_DeviceContext = GetDC(m_Hwnd);

		if (!m_DeviceContext) {
			MessageBox(NULL, "Failed to create window.", "Error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		// Find the right WGL context
		int wglAttributes[] = {
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_COLOR_BITS_ARB, 32,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_STENCIL_BITS_ARB, 8,
				WGL_SAMPLE_BUFFERS_ARB, 1, // Number of buffers (must be 1 at time of writing)
				WGL_SAMPLES_ARB, 4,        // Number of samples
				0
		};
		
		int pixelFormatID;
		UINT numFormats;

		bool status = wglChoosePixelFormatARB(m_DeviceContext, wglAttributes, NULL, 1, &pixelFormatID, &numFormats);
		
		if (status == false || numFormats == 0) {
			MessageBox(NULL, "WGL Failed to choose format.", "Error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		// Use the new pixelformatdescriptor
		PIXELFORMATDESCRIPTOR PFD;
		DescribePixelFormat(m_DeviceContext, pixelFormatID, sizeof(PIXELFORMATDESCRIPTOR), &PFD);
		SetPixelFormat(m_DeviceContext, pixelFormatID, &PFD);

		const int major_min = 3, minor_min = 2;
		int  contextAttribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
			0
		};

		m_GLContext = wglCreateContextAttribsARB(m_DeviceContext, 0, contextAttribs);
		if (m_GLContext == NULL) {
			MessageBox(NULL, "Failed to create gl context.", "Error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		// Destroy the fakes.
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(fakeGLContext);
		ReleaseDC(fakeWindow, fakeDeviceContext);
		DestroyWindow(fakeWindow);

		// Use the actual
		if (!wglMakeCurrent(m_DeviceContext, m_GLContext)) {
			MessageBox(NULL, "Failed to make context current.", "Error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		initGL();
		setVSync(vsync);

		if (full) {
			setFullscreen(true);
		}

	}

	Win32Window::~Win32Window()
	{
		if (m_Fullscreen) {
			ChangeDisplaySettings(NULL, 0);
		}
		if (m_GLContext) {
			if (!wglMakeCurrent(NULL, NULL)) {
				Console::logError("Failed to reset context");
			}
			if (!wglDeleteContext(m_GLContext))
			{
				Console::logError("Failed to delete context");
			}
		}

		if (m_DeviceContext) {
			ReleaseDC(m_Hwnd, m_DeviceContext);
		}

		if (m_Hwnd) {
			if(!DestroyWindow(m_Hwnd)){
				Console::logError("Failed to destroy window");
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

	void Win32Window::setVSync(bool f)
	{
		m_VSync = f;
		if (wglSwapIntervalEXT != NULL) {
			wglSwapIntervalEXT(f ? 1 : 0);
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

			return FALSE;
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


			InputEvent event;
			event.m_EventType = InputEvent::WindowResize;
			event.m_WindowSize = Vector2f(width, height) / dpiScale();

			m_InputEvents.push_back(event);
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


		case WM_KEYUP:
		case WM_KEYDOWN:
		{
			InputEvent event;
			event.m_EventType = message == WM_KEYUP ? InputEvent::KeyboardReleased : InputEvent::KeyboardPressed;
			event.m_KeyCode = (int) GetVirtualKey(wParam, lParam);
			event.m_Repeated = IsRepeated(lParam);

			{
				int dir = 1;

				if (message == WM_KEYUP) dir = 0;

				// TODO find if missed messages work like this.
				if (wParam == VK_CONTROL)
					m_CrtlDown = dir;
				
				if (wParam == VK_MENU)
					m_AltDown = dir;

				if (wParam == VK_SHIFT)
					m_ShiftDown = dir;

			}

			event.m_CrtlDown = m_CrtlDown > 0;
			event.m_AltDown = m_AltDown > 0;
			event.m_ShiftDown = m_ShiftDown > 0;

			m_InputEvents.push_back(event);
		}
		break;

		case WM_CHAR:
		{
			InputEvent event;
			event.m_EventType = InputEvent::KeyboardTyped;
			event.m_UnicodeKey = (int) wParam;

			if (!(HIWORD(lParam) & 0x8000)) {
				m_InputEvents.push_back(event);
			}
		}
		break;

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			InputEvent event;

			event.m_EventType = InputEvent::MousePressed;

			POINT p;

			p.x = GET_X_LPARAM(lParam);
			p.y = GET_Y_LPARAM(lParam);

			event.m_MousePosition = Vector2f(p.x, p.y) / dpiScale();

			if (message == WM_LBUTTONDOWN)
				event.m_MouseButton = 0;
			else if (message == WM_RBUTTONDOWN)
				event.m_MouseButton = 1;
			else
				event.m_MouseButton = 2;

			m_InputEvents.push_back(event);
		}

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			InputEvent event;

			event.m_EventType = InputEvent::MouseReleased;

			POINT p;

			p.x = GET_X_LPARAM(lParam);
			p.y = GET_Y_LPARAM(lParam);

			event.m_MousePosition = Vector2f(p.x, p.y) / dpiScale();

			if (message == WM_LBUTTONUP)
				event.m_MouseButton = 0;
			else if (message == WM_RBUTTONUP)
				event.m_MouseButton = 1;
			else
				event.m_MouseButton = 2;

			m_InputEvents.push_back(event);
		}

		case WM_MOUSEMOVE:
		{
			InputEvent event;

			event.m_EventType = InputEvent::MouseMove;
			

			POINT p;

			p.x = GET_X_LPARAM(lParam);
			p.y = GET_Y_LPARAM(lParam);

			event.m_MousePosition = Vector2f(p.x, p.y) / dpiScale();

			event.m_MouseDelta = event.m_MousePosition - m_MousePosition;

			m_MousePosition = event.m_MousePosition;

			m_InputEvents.push_back(event);
		}
		break;
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
		m_InputEvents.clear();


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
