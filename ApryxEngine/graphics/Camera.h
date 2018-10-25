#pragma once

#include "math/Matrix4.h"

namespace apryx {

	class Camera {
	public:
		virtual Matrix4f getMatrixView() = 0;
		virtual Matrix4f getMatrixProjection() = 0;
	};

}