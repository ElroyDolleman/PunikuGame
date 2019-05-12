#include "Game.h";

sf::Texture Assets::punikuSheet;
sf::Texture Assets::groundTexture;
sf::Texture Assets::backgroundTexture;
sf::Texture Assets::mineCartSheet;
sf::Texture Assets::gigaPunikuSheet;
sf::Texture Assets::spoonTexture;
sf::Texture Assets::startScreen;
sf::Texture Assets::gameOverScreen;

void Game::Initialize()
{
	punikuList.push_back(Puniku(&Assets::punikuSheet, sf::Vector2<float>(32, 48 + 32 * 0), Puniku::Flavour::Cream));
	punikuList.push_back(Puniku(&Assets::punikuSheet, sf::Vector2<float>(32, 48 + 32 * 1), Puniku::Flavour::Strawberry));
	punikuList.push_back(Puniku(&Assets::punikuSheet, sf::Vector2<float>(32, 48 + 32 * 2), Puniku::Flavour::Avocado));
	punikuList.push_back(Puniku(&Assets::punikuSheet, sf::Vector2<float>(32, 48 + 32 * 3), Puniku::Flavour::Chocolate));

	environment = Environment(&Assets::backgroundTexture, &Assets::groundTexture, &Assets::gigaPunikuSheet);
	mineCart = MineCart(&Assets::mineCartSheet);

	spoonSpawnTimer = 0;
	spoonSpawnInterval = 60;

	currentGamePhase = GamePhase::Start;
	
	startScreen.setTexture(Assets::startScreen);
	gameOverScreen.setTexture(Assets::gameOverScreen);

	startButtonHitbox = sf::IntRect(130, 44, 64, 26);

	deadInterval = 120;
	deadTimer = 0;
	
	text.setFont(font);
	text.setPosition(100, 6);
	score = 0;
}

void Game::LoadAssets()
{
	Assets::punikuSheet.loadFromFile("punikuSheet.png");
	Assets::groundTexture.loadFromFile("ground.png");
	Assets::backgroundTexture.loadFromFile("background.png");
	Assets::mineCartSheet.loadFromFile("mineCart.png");
	Assets::gigaPunikuSheet.loadFromFile("gigaPunikuSheet.png");
	Assets::spoonTexture.loadFromFile("spoon.png");
	Assets::startScreen.loadFromFile("startScreen.png");
	Assets::gameOverScreen.loadFromFile("gameOver.png");

	font.loadFromFile("pixelsix00.ttf");
}

void Game::Reset()
{
	spoonSpawnTimer = 0;
	spoonSpawnInterval = 60;

	environment = Environment(&Assets::backgroundTexture, &Assets::groundTexture, &Assets::gigaPunikuSheet);
	mineCart = MineCart(&Assets::mineCartSheet);

	spoons.clear();
	amountOfSpoonsInList = 0;

	score = 0;

	currentGamePhase = GamePhase::GameOver;
}

void Game::Update(sf::RenderWindow *window)
{
	currentMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	switch (currentGamePhase)
	{
		case GamePhase::GameOver:
			deadTimer++;

			if (deadTimer >= deadInterval)
			{
				deadTimer = 0;
				currentGamePhase = GamePhase::Start;
			}

			break;

		case GamePhase::Start:
			if (!prevMousePressed && currentMousePressed)
				if (startButtonHitbox.contains(sf::Mouse::getPosition(*window)))
					currentGamePhase = GamePhase::Active;

			break;

		case GamePhase::Active:

			bool gameOver = false;

			for (int i = 0; i < 4; i++)
			{
				auto puniku = punikuList.begin();
				std::advance(puniku, i);

				puniku->Update();

				if (!prevMousePressed && currentMousePressed)
					if (puniku->hitbox.contains(sf::Mouse::getPosition(*window)))
						for (int j = 0; j <= i; j++)
						{
							auto puniku2 = punikuList.begin();
							std::advance(puniku2, j);

							if (puniku2->IsInAir())
								break;
							puniku2->Jump();
						}

				for (int i = 0; i < amountOfSpoonsInList; i++)
				{
					auto spoon = spoons.begin();
					std::advance(spoon, i);

					if (!spoon->gavePoint && spoon->spoonSprite.getPosition().x < 60)
					{
						spoon->gavePoint = true;
						score++;
					}

					if (spoon->hitbox.intersects(puniku->hitbox))
					{
						gameOver = true;
						break;
					}
				}
			}

			if (amountOfSpoonsInList < maxSpoonsInList)
			{
				spoonSpawnTimer++;
				if (spoonSpawnTimer >= spoonSpawnInterval)
				{
					spoonSpawnTimer = 0;
					amountOfSpoonsInList++;

					spoons.push_back(Spoon(&Assets::spoonTexture));
				}
			}

			for (int i = 0; i < amountOfSpoonsInList; i++)
			{
				auto front = spoons.begin();
				std::advance(front, i);

				front->Update();
			}

			mineCart.Update();
			environment.Update();

			if (gameOver)
			{
				Reset();
			}
			break;
	}

	prevMousePressed = currentMousePressed;
}

void Game::Draw(sf::RenderWindow *window)
{
	

	switch (currentGamePhase)
	{
		case GamePhase::GameOver:
			window->draw(gameOverScreen);
			break;

		case GamePhase::Start:
			window->draw(startScreen);
			break;

		case GamePhase::Active:
			environment.DrawBack(window);

			for (int i = 0; i < amountOfSpoonsInList; i++)
			{
				auto front = spoons.begin();
				std::advance(front, i);

				front->Draw(window);
			}

			for (int i = 0; i < 4; i++)
			{
				auto front = punikuList.begin();
				std::advance(front, i);

				front->Draw(window);
			}

			mineCart.Draw(window);
			environment.DrawFront(window);

			std::ostringstream stringScore;
			stringScore << score;

			text.setString(stringScore.str());

			window->draw(text);
			break;
	}
}