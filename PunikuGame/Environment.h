#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

class Environment
{
	public:
		sf::Sprite background;
		std::list<sf::Sprite> gigaPunikuList;
		sf::Sprite groundLeft, groundRight;

		float speed;

		Environment();
		Environment(sf::Texture *backgroundTex, sf::Texture *groundTex, sf::Texture *gigaPunikuTex);

		void Update();
		void DrawBack(sf::RenderWindow *window);
		void DrawFront(sf::RenderWindow *window);
};