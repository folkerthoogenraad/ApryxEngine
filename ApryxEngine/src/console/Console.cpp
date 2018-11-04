#include "Console.h"

#include <iostream>

namespace apryx {

	std::vector<std::string> apryx::Console::history;

	void apryx::Console::log(const std::string & message)
	{
		std::cout << message << std::endl;
		history.push_back(message);
	}

	void apryx::Console::logError(const std::string & message)
	{
		std::cerr << message << std::endl;
	}

	void apryx::Console::pause()
	{
		std::cout << "Press any key to continue... ";
		std::cin.get();
	}
}