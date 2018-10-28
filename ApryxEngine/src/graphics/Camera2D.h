#pragma once

#include "Camera.h"

#include "math/Vector2.h"

namespace apryx {

	class Camera2D : public Camera{
		float m_Near = -1000;
		float m_Far = 1000;
	public:
		Vector2f size;
		Vector2f position;
		bool flipped = false;
	public:
		Camera2D(float width, float height, bool flipped = false);

		virtual Matrix4f getMatrixView();
		virtual Matrix4f getMatrixProjection();

		void setWidth(float width) { size.x = width; }
		void setHeight(float height) { size.y = height; }

		void setNear(float n) { m_Near = n; }
		void setFar(float f) { m_Far = f; }

		float getWidth() const { return size.x; }
		float getHeight() const { return size.y; }

		float getNear() const { return m_Near; }
		float getFar() const { return m_Far; }
	};

}