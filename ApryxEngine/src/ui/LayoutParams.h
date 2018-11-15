#pragma once

#include "math/Vector2.h"

// TODO add exact scaling
namespace apryx {

	// The class that holds information about the layout parameters, like the scaling preferences
	class LayoutParams {
	public:
		enum LayoutScaling {
			//Exact, 
			WrapContent, 
			MatchParent
		};

		LayoutScaling m_WidthScaling = WrapContent;
		LayoutScaling m_HeightScaling = WrapContent;

		// For when Exact
		// Vector2f m_Size = Vector2f(-1, -1);

		// For when MatchParent
		Vector2f m_Weight = Vector2f(1, 1);

		LayoutParams() {}
		LayoutParams(LayoutScaling width, LayoutScaling height) :m_WidthScaling(width), m_HeightScaling(height) {}
		LayoutParams(LayoutScaling width, LayoutScaling height, Vector2f weight) :m_WidthScaling(width), m_HeightScaling(height), m_Weight(weight) {}

	};

}