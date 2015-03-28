#include <SFML/Graphics.hpp>

class MineCart
{
	public:
		int timer;

		sf::IntRect source;
		sf::Sprite cart;

		MineCart();
		MineCart(sf::Texture *mineCartTex);

		void Update();
		void Draw(sf::RenderWindow *window);
};