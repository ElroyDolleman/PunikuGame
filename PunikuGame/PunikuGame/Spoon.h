#include <SFML/Graphics.hpp>

class Spoon
{
	public:
		sf::Sprite spoonSprite;
		sf::IntRect hitbox;
		float speed;
		bool gavePoint;

		Spoon();
		Spoon(sf::Texture *spoonTexture);

		void Update();
		void Draw(sf::RenderWindow *window);
};