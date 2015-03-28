#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Puniku.h";
#include "Assets.h";
#include "Environment.h";
#include "MineCart.h";
#include "Spoon.h";
#include <sstream>

class Game
{
	public:
		enum class GamePhase { Start = 0, Active = 1, GameOver = 2 };
		GamePhase currentGamePhase;

		void Initialize();
		void LoadAssets();
		void Update(sf::RenderWindow *window);
		void Draw(sf::RenderWindow *window);

		void Reset();

		std::list<Puniku> punikuList;
		std::list<Spoon> spoons;

		Environment environment;
		MineCart mineCart;

		bool prevMousePressed, currentMousePressed;

		float spoonSpawnTimer, spoonSpawnInterval;
		int maxSpoonsInList = 2, amountOfSpoonsInList = 0;

		float deadTimer, deadInterval;

		sf::Sprite startScreen;
		sf::Sprite gameOverScreen;
		sf::IntRect startButtonHitbox;

		int score;
		sf::Font font;
		sf::Text text;
};