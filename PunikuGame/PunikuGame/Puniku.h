#include <SFML/Graphics.hpp>
#include <iostream>
#include "Math.h";

class Puniku
{
	public:
		enum class Flavour { Cream = 32*0, Strawberry = 32*1, Chocolate = 32*2, Cherry = 32*3, Avocado = 32*4, Blueberry = 32*5 };

		sf::Sprite body;

		sf::IntRect hitbox;
		sf::Vector2<float> position;
		int landingPosition;

		float gravity = 0.22f;
		float jumpPower = 5;

		float fallSpeed = 0;
		float maxFallSpeed = 4;

		Flavour flavour;

		Puniku();
		Puniku(sf::Texture *bodyTex, sf::Vector2<float> position, Flavour flavour);

		void Update();
		void Draw(sf::RenderWindow *window);

		void Jump();
		bool IsInAir();
};