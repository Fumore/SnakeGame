#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include "SnakeNode.h"
namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position , int i);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	int k;

    sf::Vector2f position_;//位置
	void move(float xOffset, float yOffset);
	void setPosition(float x, float y);

	void firstrender(sf::RenderWindow& window,SnakeNode head);//第一人称视角

private:
	sf::CircleShape shape_;

	static const float Radius;
}; 
}

#endif