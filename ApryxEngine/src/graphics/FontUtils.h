#pragma once

#include "resources/Context.h"
#include "Font.h"
#include <string>

namespace apryx {

	std::shared_ptr<Font> createDefaultFont(Context &context);
	std::shared_ptr<Font> loadBitmapFont(Context &context, const std::string &folder, const std::string &font);

	void writeImageAsCPP(const std::string &file, const Image &image);
	
}