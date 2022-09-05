#include "Menu/Exit.h"

Exit::Exit(sf::RenderWindow& window)
	:m_window(window) 
{
}

void Exit::execute()
{
	m_window.close();
	exit(EXIT_SUCCESS);
}