#include "Paint.h"

namespace apryx {
	Paint::Paint()
		: m_Color(Color32::white())
	{

	}

	Paint::Paint(Color32 color)
		: m_Color(color)
	{
	}
}
