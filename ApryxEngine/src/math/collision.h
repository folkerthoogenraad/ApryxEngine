#pragma once

#include <optional>
#include "math.h"

namespace apryx {

	//Forward declare all the way !
	template <typename T>
	struct Vector2;
	template <typename T>
	struct Vector3;
	template <typename T>
	struct Vector4;
	template <typename T>
	struct Circle;
	template <typename T>
	struct Sphere;
	template <typename T>
	struct Line2;
	template <typename T>
	struct Line3;
	template <typename T>
	struct Plane;
	template <typename T>
	struct Rectangle;

	template<typename T>
	T distance(const Vector2<T> &a, const Vector2<T> &b)
	{
		return (b - a).magnitude();
	}
	
	template<typename T>
	T distance(const Vector3<T> &a, const Vector3<T> &b)
	{
		return (b - a).magnitude();
	}
	
	template<typename T>
	T distance(const Vector4<T> &a, const Vector4<T> &b)
	{
		return (b - a).magnitude();
	}

	template<typename T>
	std::optional<Vector2<T>> intersect(const Line2<T> &l1, const Line2<T> &l2)
	{
		//p + t r = q + u s

		//p = origin1
		//q = origin2
		//r = dir1
		//s = dir2

		T d = Vector2<T>::cross(l1.direction(), l2.direction());

		if (d == 0)
			return std::nullopt;

		return l1.origin() + l1.direction() * (
			Vector2<T>::cross(l2.origin() - l1.origin(), l2.direction()) / d );
	}

	template<typename T>
	std::optional<Vector2<T>> intersectSegment(const Line2<T> &l1, const Line2<T> &l2)
	{
		//p + t r = q + u s

		//p = origin1
		//q = origin2
		//r = dir1
		//s = dir2

		T d = Vector2<T>::cross(l1.direction(), l2.direction());

		//TODO fix this function

		if (d == 0)
			return std::nullopt;

		float b = Vector2<T>::cross(l1.origin() - l2.origin(), l1.direction()) / d;
		
		if (b < 0)
			return std::nullopt;
		if (b > 1)
			return std::nullopt;


		float f = Vector2<T>::cross(l2.origin() - l1.origin(), l2.direction()) / d;

		if (f < 0)
			return std::nullopt;
		if (f > 1)
			return std::nullopt;

		return l1.origin() + l1.direction() * f;
	}

	template<typename T>
	std::optional<Rectangle<T>> intersect(const Rectangle<T> &r1, const Rectangle<T> &r2)
	{
		T left = max_t(r1.left(), r2.left());
		T right = min_t(r1.right(), r2.right());

		T width = right - left;

		if (width < 0)
			return std::nullopt;

		T top = max_t(r1.top(), r2.top());
		T bottom = min_t(r1.bottom(), r2.bottom());

		T height = bottom - top;

		if (height < 0)
			return std::nullopt;

		return Rectangle<T>(left, top, width, height);
	}

	template<typename T>
	std::optional<T> intersect(const Circle<T> &c, const Circle<T> &other) {
		T t = (c.radius + other.radius) - distance(c.center, other.center);

		if (t >= 0)
			return t;
		else
			return std::nullopt;
	}

	template<typename T>
	std::optional<T> intersect(const Sphere<T> &c, const Sphere<T> &other) {
		T t = (c.radius + other.radius) - distance(c.center, other.center);

		if (t >= 0)
			return t;
		else
			return std::nullopt;
	}
	
	template<typename T>
	std::optional<Vector3<T>> intersect(const Plane<T> &plane, const Line3<T> &line) 
	{
		Vector3<T> lineDir = line.direction();

		T directionalDot = Vector3<T>::dot(lineDir, plane.direction);

		if (directionalDot == 0)
			return std::nullopt;

		T planerDot = -(Vector3<T>::dot(plane.direction, line.a) + plane.offset);

		T result = planerDot / directionalDot;

		return line.a + lineDir * result;
	}

	template<typename T>
	std::optional<Line3<T>>	intersect(const Plane<T> &p, const Plane<T> &other)
	{
		Vector3<T> dir = Vector3<T>::cross(other.direction, p.direction);

		if (dir.sqrmagnitude() == 0)
			return std::nullopt;

		//Perform a line intersection with the other plane
		Line3<T> line(p.origin(), p.origin() + Vector3<T>::cross(dir, p.direction));

		//TODO check if this is needed.
		Vector3<T> o = intersect(other, line).result;

		return Line3<T>(o, o + dir);
	}

	template<typename T>
	bool overlaps(const Rectangle<T> &a, const Rectangle<T> &b) {
		if (a.right() > b.left()) return false;
		if (b.right() > a.left()) return false;

		if (a.bottom() < b.top()) return false;
		if (b.bottom() < a.top()) return false;

		return true;
	}

	template<typename T>
	bool contains(const Circle<T> &c, const Vector2<T> &point) {
		return distance(c.center, point) <= c.radius;
	}

	template<typename T>
	bool contains(const Rectangle<T> &c, const Vector2<T> &point) {
		// Oh boy, y up vs y down
		// This might be very wrong...
		return !(point.x <= c.left() && point.x >= c.right() 
			&& point.y <= c.bottom() && point.y >= c.top());
	}

	template<typename T>
	bool contains(const Rectangle<T> &outer, const Rectangle<T> &inner) {
		if (outer.left() > inner.left()) return false;
		if (outer.right() < inner.right()) return false;
		if (outer.top() > inner.top()) return false;
		if (outer.bottom() < inner.bottom()) return false;
		return true;
	}
	
	template<typename T>
	bool contains(const Sphere<T> &c, const Vector3<T> &point) {
		return distance(c.center, point) <= c.radius;
	}

}