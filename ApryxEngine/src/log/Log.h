#pragma once

#include <string>

namespace apryx {
	class Debug {
	public:
		template<typename T>
		static void log(const T &message)
		{
			std::cout << message << std::endl;
		}

		static void log(const std::string &message);
		static void logError(const std::string &message);
		static void pause();
	};
}