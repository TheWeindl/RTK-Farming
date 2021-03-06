// SFML_Test.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "SFML/Graphics.hpp"
#include "Field.h"
#include "GPSPoint.h"
#include "Path.h"
#include "Traktor.h"

#include <iostream>
#include <iomanip>

/*
Defines for debug prints 
If something is defined in gets printed
Possibilities are:
	PRINT_DEBUG
	PRINT_INFO
	NO_GUI
*/
#define PRINT_INFO
//#define NO_GUI
/*
int main()
{
#ifndef NO_GUI
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "RTK Simulation SFML", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);
#endif // !NO_GUI

	sf::Vector2f fieldPosition(9750.0f, 9500.0f);
	sf::View view(fieldPosition, sf::Vector2f(512.0f, 512.0f));
	view.setSize(sf::Vector2f(100.0f, 100.0f));

	std::cout << "Welcome to the RTK Simulator" << std::endl;

	std::vector<GPSPoint> points = {	{ 47.973607, 13.952491 },
										{ 47.972866, 13.949628 },
										{ 47.973522, 13.949010 },
										{ 47.973733, 13.949565 },
										{ 47.974926, 13.948515 },
										{ 47.975569, 13.951953 },
										{ 47.974847, 13.952697 },
										{ 47.974686, 13.952145 },
										{ 47.974349, 13.952088 },
										{ 47.974278, 13.951889 } };
	Field field(points);
	field.getShape().setFillColor(sf::Color::Yellow);
	view.setCenter(fieldPosition);

	Path path;
	path.calcPath(&field);

	Traktor traktor;
	traktor.updatePosition(47.972866, 13.949628);

#ifdef PRINT_INFO
	field.printEdgeLengths();
#endif // PRINT_INFO

#ifndef NO_GUI
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
		{
			view.zoom(1.01f);
			std::cout << "Zoom out" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		{
			view.zoom(0.99f);
			std::cout << "Zoom in" << std::endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			view.move(sf::Vector2f(-0.1f,0.0f));
			std::cout << "Move left" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			view.move(sf::Vector2f(0.1f, 0.0f));
			std::cout << "Move right" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			view.move(sf::Vector2f(0.0f, -0.1f));
			std::cout << "Move up" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			view.move(sf::Vector2f(0.0f, 0.1f));
			std::cout << "Move down" << std::endl;
		}

		//Clear the screen for the next render cylce
		window.clear(sf::Color(150, 150, 150));

		//Set the view on the buffer
		window.setView(view);

		//Draw all objects to the back buffer
		window.draw(field.getShape());
		window.draw(traktor.getShape());

		//Swapp the back buffer to the front buffer -> render the buffer to the screen
		window.display();
	}
#endif // !NO_GUI

	return 0;
}
*/
