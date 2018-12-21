#pragma once

#include "Vector2.h"

namespace apryx {

	template<typename T>
	struct Line2{
		Vector2<T> position;
		Vector2<T> direction;

		Line2() {}
		Line2(const Vector2<T> &pos, const Vector2<T> &dir)
			: position(pos), direction(dir) {}

		Vector2<T> perp() const
		{
			return Vector2<T>::perp(direction);
		}

		Line2<T> normal() const
		{
			Vector2<T> p = perp();
			return Line2<T>(position, p);
		}

		T distanceFrom(const Vector2<T> &p)
		{
			return Vector2<T>::dot(p - position, perp());
		}

		LineSegment2<T> &translate(Vector2f v)
		{
			position += v;

			return *this;
		}

		Line2<T> clone()
		{
			return Line2<T>(*this);
		}

		Line2<T> flipped()
		{
			return clone().flip();
		}

		Line2<T> &flip()
		{
			direction = -direction;
			return *this;
		}
	};


	typedef Line2<float> Line2f;
	typedef Line2<double> Line2d;
}