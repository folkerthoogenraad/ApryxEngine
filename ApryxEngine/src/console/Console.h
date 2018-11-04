#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace apryx {
	class Console {
	public:
		static std::vector<std::string> history;

		static void log(const std::string &message);

		template<typename T>
		static void log(const T &message)
		{
			std::stringstream stream;
			stream << message;

			log(stream.str());
		}

		static void logError(const std::string &message);
		static void pause();
	};
}