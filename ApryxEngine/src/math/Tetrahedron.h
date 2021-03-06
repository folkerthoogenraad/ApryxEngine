#pragma once

#include "Vector3.h"

namespace apryx {


	template<typename T>
	struct Sphere;

	template<typename T>
	struct Triangle3;

	template<typename T>
	struct Matrix4;

	template<typename T>
	struct Tetrahedron {
		Vector3<T> a;
		Vector3<T> b;
		Vector3<T> c;
		Vector3<T> d;

		Tetrahedron() {}
		Tetrahedron(const Vector3<T> &a, const Vector3<T> &b, const Vector3<T> &c, const Vector3<T> &d)
			: a(a), b(b), c(c), d(d) {}

		Sphere<T> circumsphere()
		{
			//http://mathworld.wolfram.com/CircumSphere.html
			//Don't even bother

			T aa = Matrix4<T>({
				a.x, a.y, a.z, 1,
				b.x, b.y, b.z, 1,
				c.x, c.y, c.z, 1,
				d.x, d.y, d.z, 1
			}).determinant();

			T dx = Matrix4<T>({
				a.sqrmagnitude(), a.y, a.z, 1,
				b.sqrmagnitude(), b.y, b.z, 1,
				c.sqrmagnitude(), c.y, c.z, 1,
				d.sqrmagnitude(), d.y, d.z, 1
			}).determinant();

			T dy = -Matrix4<T>({
				a.sqrmagnitude(), a.x, a.z, 1,
				b.sqrmagnitude(), b.x, b.z, 1,
				c.sqrmagnitude(), c.x, c.z, 1,
				d.sqrmagnitude(), d.x, d.z, 1
			}).determinant();

			T dz = Matrix4<T>({
				a.sqrmagnitude(), a.x, a.y, 1,
				b.sqrmagnitude(), b.x, b.y, 1,
				c.sqrmagnitude(), c.x, c.y, 1,
				d.sqrmagnitude(), d.x, d.y, 1
			}).determinant();

			T cc = Matrix4<T>({
				a.sqrmagnitude(), a.x, a.y, a.z,
				b.sqrmagnitude(), b.x, b.y, b.z,
				c.sqrmagnitude(), c.x, c.y, c.z,
				d.sqrmagnitude(), d.x, d.y, d.z
			}).determinant();

			return Sphere<T>(
				Vector3<T>(dx / (2 * aa), dy / (2 * aa), dz / (2 * aa)),
				sqrt(dx * dx + dy * dy + dz * dz - 4 * aa * cc) / (2.0f * abs(aa))
				);
		}
		
		Tetrahedron<T> &transform(const Matrix4<T> &m)
		{
			a = m * a;
			b = m * b;
			c = m * c;
			d = m * d;
			return *this;
		}
		Tetrahedron<T> transformed(const Matrix4<T> &m) const
		{
			return clone().transform(m);
		}

		//Orients all the normals outside
		Tetrahedron<T> &orient()
		{
			if (trianglebdc().distanceFrom(a) > 0) {
				Vector3<T> t = b;
				b = c;
				c = t;
			}

			return *this;
		}
		
		Tetrahedron<T> &flip()
		{
			Vector3<T> t = b;
			b = c;
			c = t;
			return *this;
		}
		Tetrahedron<T> flipped() const 
		{
			return clone().flip();
		}
		
		Tetrahedron<T> clone()
		{
			return Tetrahedron<T>(*this);
		}

		Vector3<T> center()
		{
			return (a + b + c + d) / 4;
		}

		Triangle3<T> triangleabc() const { return Triangle3<T>(a, b, c); }
		Triangle3<T> triangleadb() const { return Triangle3<T>(a, d, b); }
		Triangle3<T> triangleacd() const { return Triangle3<T>(a, c, d); }
		Triangle3<T> trianglebdc() const { return Triangle3<T>(b, d, c); }
	
		static Tetrahedron<T> unitTetrahedron()
		{
			//TODO im not sure how this should play out honestly.
			//This is a template so you can't just do this easily
			T w = (T) (sqrt(0.75) / 3.0);
			T h = (T) (sqrt( 1 - (2 * w) * (2 * w) ) / 3.0);

			return Tetrahedron<T>(
				Vector3<T>(0, -h, 2.f * w),	//A
				Vector3<T>(-0.5, -h, -w),		//B
				Vector3<T>(0.5, -h, -w),		//C
				Vector3<T>(0, 2 * h, 0)		//D
				);
		}
	};

	typedef Tetrahedron<float> Tetrahedronf;
	typedef Tetrahedron<double> Tetrahedrond;
	typedef Tetrahedron<int> Tetrahedroni;

}