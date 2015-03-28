#include "Puniku.h"

Puniku::Puniku()
{

}

Puniku::Puniku(sf::Texture *bodyTex, sf::Vector2<float> position, Flavour flavour)
{
	this->body.setTexture(*bodyTex);

	this->position = position;
	this->landingPosition = position.y;

	this->flavour = flavour;
	this->body.setTextureRect(sf::IntRect((int)flavour, 0, 32, 32));

	this->hitbox = sf::IntRect(position.x, position.y, 32, 32);
}

void Puniku::Update()
{
	fallSpeed = Math::Min(fallSpeed + gravity, maxFallSpeed);

	position.y = Math::Clamp(position.y + fallSpeed, landingPosition - 32, landingPosition);

	hitbox.left = position.x;
	hitbox.top = position.y;
}

void Puniku::Jump()
{
	fallSpeed = -jumpPower;
}

void Puniku::Draw(sf::RenderWindow *window)
{
	body.setPosition(position);

	window->draw(body);
}

bool Puniku::IsInAir()
{
	return position.y != landingPosition;
}