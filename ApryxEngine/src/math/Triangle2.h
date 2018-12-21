#pragma once

#include "collision.h" //TODO not need this

#include "Vector2.h"

namespace apryx {

	template<typename T>
	struct Triangle2 {
		Vector2<T> a;
		Vector2<T> b;
		Vector2<T> c;

		Triangle2() {}
		Triangle2(const Vector2<T> &a, const Vector2<T> &b, const Vector2<T> &c)
			: a(a), b(b), c(c) {}

		bool hasVertex(Vector2<T> v)
		{
			return a == v || b == v || c == v;
		}
		
		Vector2<T> center()
		{
			return (a + b + c) / 3;
		}

		Triangle2<T> &orient()
		{
			//Normals pointing outwards
			//Flip b and c if the winding is reversed
			if (edgeab().distanceFrom(c) > 0) {
				Vector2<T> t = b;
				b = c;
				c = t;
			}

			return *this;
		}

		Triangle2<T> clone()
		{
			return Triangle2<T>(*this);
		}

		Vector2<T> circumcenter()
		{
			return intersect(
				LineSegment2<T>(b, a).normal(),
				LineSegment2<T>(b, c).normal()
			).result;
		}

		Circle<T> circumcircle()
		{
			auto center = circumcenter();
			return Circle<T>(
				center,
				distance(a, center)
				);
		}

		bool isValid()
		{
			return intersects(
				LineSegment2<T>(b, a),
				LineSegment2<T>(b, c)
			);
		}

		LineSegment2<T> edgeab() const { return LineSegment2<T>(a, b); }
		LineSegment2<T> edgebc() const { return LineSegment2<T>(b, c); }
		LineSegment2<T> edgeca() const { return LineSegment2<T>(c, a); }
	};

	typedef Triangle2<float> Triangle2f;
	typedef Triangle2<double> Triangle2d;
	typedef Triangle2<int> Triangle2i;
	typedef Triangle2<long long> Triangle2ll;

}