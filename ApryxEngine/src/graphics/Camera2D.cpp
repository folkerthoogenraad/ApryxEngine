#include "Camera2D.h"

namespace apryx {

	Camera2D::Camera2D(float width, float height, bool flipped)
		: size(width, height), flipped(flipped)
	{ }

	Matrix4f Camera2D::getMatrixView()
	{
		return Matrix4f::translation(position.x, position.y, 0);
	}

	Matrix4f Camera2D::getMatrixProjection()
	{
		if (flipped)
			return Matrix4f::orthographic(0, size.x, 0, size.y, m_Near, m_Far);
		else
			return Matrix4f::orthographic(0, size.x, size.y, 0, m_Near, m_Far);
	}


}
