#include "Menu/Menu.h"
#include <cstdlib>
#include <iostream>

int main() try
{
	Menu menu;
	menu.show();

	return EXIT_SUCCESS;
}
catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return EXIT_FAILURE;
}
catch (...) {
    std::cerr << "Unknown exception\n";
    return EXIT_FAILURE;
}