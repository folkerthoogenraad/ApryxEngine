#pragma once

#include "Texture.h"
#include "Graphics2D.h"

namespace apryx {

	class Surface : public Texture {
	public:
		virtual Graphics2D &getGraphics() = 0;
	};

}