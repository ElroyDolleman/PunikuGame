#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h";

int main()
{
	sf::RenderWindow window(sf::VideoMode(320, 240), "Puniku");

	Game game;
	game.LoadAssets();
	game.Initialize();

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//std::cout <<  << std::endl;

		window.clear();

		game.Update(&window);
		game.Draw(&window);

		window.display();
	}

}