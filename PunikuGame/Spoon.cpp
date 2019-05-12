#include "Spoon.h";
#include <iostream>

Spoon::Spoon()
{
	
}

Spoon::Spoon(sf::Texture *spoonTexture)
{
	this->spoonSprite.setTexture(*spoonTexture);
	this->spoonSprite.setPosition(320, 16 + (rand() % 4 * 32));

	this->hitbox = sf::IntRect(spoonSprite.getPosition().x, spoonSprite.getPosition().y, 8, 32-16);

	speed = 4;

	gavePoint = false;
}

void Spoon::Update()
{
	spoonSprite.move(-speed, 0);

	if (spoonSprite.getPosition().x < -48)
	{
		spoonSprite.setPosition(360, 16 + (rand() % 5 * 32));
		gavePoint = false;
	}

	hitbox.left = spoonSprite.getPosition().x;
	hitbox.top = spoonSprite.getPosition().y + 8;
}

void Spoon::Draw(sf::RenderWindow *window)
{
	window->draw(spoonSprite);
}