#pragma once

#include "math/Vector2.h"

namespace apryx {

	class Image;

	class Texture {
	public:
		enum WrappingMode {
			Clamp,
			Repeat
		};
		enum TextureFiltering {
			Linear,
			NearestNeighbour
		};
	public:
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void setFiltering(TextureFiltering filtering) = 0;
		virtual void setWrapping(WrappingMode wrapping) = 0;

		Vector2f getSize() const { return Vector2f((float)getWidth(), (float)getHeight()); }

		virtual void setData(const Image &image) = 0;
	};

}