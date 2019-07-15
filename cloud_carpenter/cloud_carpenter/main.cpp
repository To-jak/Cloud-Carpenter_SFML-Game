#include <Application.hpp>

#include <stdexcept>
#include <iostream>


int main()
{
	try
	{
		// On relegue tout � la classe Application et on r�cup�re toutes les exceptions
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
