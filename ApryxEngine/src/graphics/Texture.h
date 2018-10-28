#pragma once

#include "math/Vector2.h"

namespace apryx {

	class Image;

	class Texture {
	public:
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		Vector2f getSize() const { return Vector2f(getWidth(), getHeight()); }

		virtual void setData(const Image &image) = 0;
	};

}