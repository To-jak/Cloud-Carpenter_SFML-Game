#include <Application.hpp>

#include <stdexcept>
#include <iostream>


int main()
{
	try
	{
		// On relegue tout à la classe Application et on récupère toutes les exceptions
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
