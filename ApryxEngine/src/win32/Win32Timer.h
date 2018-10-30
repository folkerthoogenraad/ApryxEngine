#pragma once

#include <windows.h>

namespace apryx {

	class Win32Timer {
		bool m_Running = false;

		LARGE_INTEGER m_Start;
		LARGE_INTEGER m_Previous;
		LARGE_INTEGER m_End;

		LARGE_INTEGER m_Frequency;
	public:
		Win32Timer();

		void start();

		// Both in seconds
		double lap();
		double runtime();

		void end();

		static void sleep(double seconds);
	};

}