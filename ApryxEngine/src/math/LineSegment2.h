#pragma once

#include "Vector2.h"
#include "Matrix2.h"

//TODO refactor this thing

namespace apryx {
	template<typename T>
	struct LineSegment2 {
		Vector2<T> a;
		Vector2<T> b;

		LineSegment2() {}
		LineSegment2(const Vector2<T> &a, const Vector2<T> &b)
			: a(a), b(b) {}

		Vector2<T> direction() const
		{
			return b - a;
		}

		Vector2<T> perp() const
		{
			return Vector2<T>::perp(direction());
		}

		const Vector2<T> &origin() const
		{
			return a;
		}

		Vector2<T> center() const
		{
			return (a + b) / (T)2.0;
		}

		LineSegment2<T> normal() const
		{
			Vector2<T> p = perp();
			return LineSegment2<T>(center(), center() + p);
		}

		//The distance from point to line in 'line units' (its complicated. If the line is normalized its just normal direction)
		T distanceFrom(const Vector2<T> &p)
		{
			return Vector2<T>::dot(p - a, perp());
		}

		T length() const
		{
			return distance(a, b);
		}

		LineSegment2<T> &translate(Vector2f v)
		{
			a += v;
			b += v;

			return *this;
		}

		LineSegment2<T> clone()
		{
			return LineSegment2<T>(*this);
		}

		LineSegment2<T> flipped()
		{
			return clone().flip();
		}

		LineSegment2<T> &flip()
		{
			auto aa= a;
			a = b;
			b = aa;
			return *this;
		}
	};

	typedef LineSegment2<float> LineSegment2f;
	typedef LineSegment2<double> LineSegment2d;
	typedef LineSegment2<int> LineSegment2i;
	typedef LineSegment2<long long> LineSegment2ll;
}