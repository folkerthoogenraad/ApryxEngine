#pragma once

#include <string>

namespace apryx {
	class Debug {
	public:
		static void log(const std::string &message);
		static void logError(const std::string &message);
		static void pause();
	};
}