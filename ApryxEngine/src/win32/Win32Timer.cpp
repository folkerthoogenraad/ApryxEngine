#include "Win32Timer.h"

namespace apryx {

	Win32Timer::Win32Timer()
	{
		QueryPerformanceFrequency(&m_Frequency);
	}

	void Win32Timer::start()
	{
		m_Running = true;

		QueryPerformanceCounter(&m_Start);
		m_Previous = m_Start;
	}

	double Win32Timer::lap()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);

		double result = 
			(double)(current.QuadPart - m_Previous.QuadPart) /
			(double)m_Frequency.QuadPart;

		m_Previous = current;
		return result;
	}

	double Win32Timer::runtime()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);

		double result =
			(double)(current.QuadPart - m_Start.QuadPart) /
			(double)m_Frequency.QuadPart;

		return result;
	}

	void Win32Timer::end()
	{
		m_Running = false;

		QueryPerformanceCounter(&m_End);
	}

	void Win32Timer::sleep(double seconds)
	{
		Sleep((DWORD)seconds * 1000);
	}
}
