#pragma once

#include "Vector3.h"

namespace apryx {

	template<typename T>
	struct Matrix4;

	template<typename T>
	struct LineSegment3 {
		Vector3<T> a;
		Vector3<T> b;

		LineSegment3() {}
		LineSegment3(const Vector3<T> &a, const Vector3<T> &b)
			: a(a), b(b) {}

		Vector3<T> direction() const
		{
			return b - a;
		}
		Vector3<T> perp() const
		{
			return Vector3<T>::perp(direction());
		}

		const Vector3<T> &origin() const
		{
			return a;
		}
		Vector3<T> center() const
		{
			return (a + b) / (T)2.0;
		}

		LineSegment3<T> normal() const
		{
			Vector3<T> p = perp();
			return LineSegment3<T>(center(), center() + p);
		}

		//The distance from point to line in line units
		T distanceFrom(const Vector3<T> p)
		{
			return Vector3<T>::dot(p - a, perp());
		}

		T sqrmagnitude() const
		{
			return (b - a).sqrmagnitude();
		}
		T magnitude() const
		{
			return (b - a).magnitude();
		}

		LineSegment3<T> clone()
		{
			return LineSegment3<T>(*this);
		}

		LineSegment3<T> &flip()
		{
			T temp = a;
			a = b;
			b = temp;

			return *this;
		}
		LineSegment3<T> flipped() const
		{
			return clone().flip();
		}
	
		LineSegment3<T> &transform(const Matrix4<T> &m)
		{
			a = m * a;
			b = m * b;
			return *this;
		}
		LineSegment3<T> transformed(const Matrix4<T> &m) const
		{
			return clone().transform(m);
		}
	};

	typedef LineSegment3<float> LineSegment3f;
	typedef LineSegment3<double> LineSegment3d;
	typedef LineSegment3<int> LineSegment3i;
}