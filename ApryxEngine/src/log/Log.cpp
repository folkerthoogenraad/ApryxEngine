#include "Log.h"

#include <iostream>

namespace apryx {
	void apryx::Debug::log(const std::string & message)
	{
		std::cout << message << std::endl;
	}

	void apryx::Debug::logError(const std::string & message)
	{
		std::cerr << message << std::endl;
	}

	void apryx::Debug::pause()
	{
		std::cout << "Press any key to continue... ";
		std::cin.get();
	}
}