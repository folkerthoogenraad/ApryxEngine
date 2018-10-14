#pragma once

#include "math/Vector2.h"

namespace apryx {

	class Image;

	class Texture {
	public:
		virtual float getWidth() const = 0;
		virtual float getHeight() const = 0;

		virtual Vector2f getSize() const { return Vector2f(getWidth(), getHeight()); }

		virtual void setData(const Image &image) = 0;
	};

}