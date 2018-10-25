#pragma once

#include "Texture.h"
#include "Graphics2D.h"

namespace apryx {

	class Surface {
	public:
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual std::shared_ptr<Texture> getTexture() const = 0;
		virtual Graphics2D &getGraphics() = 0;
	};

}