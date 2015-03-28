#include "Environment.h";

Environment::Environment()
{

}

Environment::Environment(sf::Texture *backgroundTex, sf::Texture *groundTex, sf::Texture *gigaPunikuTex)
{
	background.setTexture(*backgroundTex);

	groundLeft.setTexture(*groundTex);
	groundRight.setTexture(*groundTex);
	
	speed = 2;
	groundLeft.setPosition(0, 176);
	groundRight.setPosition(320, 176);

	gigaPunikuList = std::list<sf::Sprite>();
	gigaPunikuList.push_back(sf::Sprite(*gigaPunikuTex, sf::IntRect(0, 0, 128, 128)));
	gigaPunikuList.push_back(sf::Sprite(*gigaPunikuTex, sf::IntRect(128, 0, 128, 128)));
	gigaPunikuList.push_back(sf::Sprite(*gigaPunikuTex, sf::IntRect(128*2, 0, 128, 128)));
	gigaPunikuList.push_back(sf::Sprite(*gigaPunikuTex, sf::IntRect(128*3, 0, 128, 128)));

	for (int i = 0; i < 4; i++)
	{
		auto front = gigaPunikuList.begin();
		std::advance(front, i);

		front->setPosition(128 * i, 112);
	}
}

void Environment::Update()
{
	groundLeft.move(-speed, 0);

	if (groundLeft.getPosition().x <= -320)
		groundLeft.move(320, 0);

	groundRight.setPosition(groundLeft.getPosition().x + 320, groundLeft.getPosition().y);

	for (int i = 0; i < 4; i++)
	{
		auto front = gigaPunikuList.begin();
		std::advance(front, i);

		front->move(-speed/2, 0);

		if (front->getPosition().x <= -128)
			front->move(128 * 4, 0);
	}
}

void Environment::DrawBack(sf::RenderWindow *window)
{
	window->draw(background);

	for (int i = 0; i < 4; i++)
	{
		auto front = gigaPunikuList.begin();
		std::advance(front, i);

		window->draw(*front);
	}
}

void Environment::DrawFront(sf::RenderWindow *window)
{
	window->draw(groundLeft);
	window->draw(groundRight);
}