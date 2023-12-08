#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Bg
{
public:
	Bg(sf::Texture* texture, float speed);
	void Update(float deltatime);
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body[2];
	sf::Vector2f position;
	sf::Vector2f size;

	float speed;
};
