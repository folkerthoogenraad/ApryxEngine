#pragma once

#include "resources/Context.h"
#include "Font.h"
#include <string>

namespace apryx {

	std::shared_ptr<Font> createDefaultFont(Context &context);

	void writeImageAsCPP(const std::string &file, const Image &image);
}