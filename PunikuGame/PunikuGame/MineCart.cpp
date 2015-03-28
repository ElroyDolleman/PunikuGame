#include "MineCart.h";

MineCart::MineCart()
{

}

MineCart::MineCart(sf::Texture *mineCartTex)
{
	this->timer = 0;

	this->cart.setTexture(*mineCartTex);
	this->cart.setPosition(32, 176);

	this->source = sf::IntRect(0, 0, 32, 24);
}

void MineCart::Update()
{
	timer++;

	if (timer >= 15)
	{
		timer = 0;

		if (source.left == 0)
			source.left = 32;
		else
			source.left = 0;
	}
}

void MineCart::Draw(sf::RenderWindow *window)
{
	cart.setTextureRect(source);

	window->draw(cart);
}