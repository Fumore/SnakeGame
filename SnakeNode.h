#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window);
    void firstrender(sf::RenderWindow& window,SnakeNode head);//第一人称视角绘制
	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;
    void setangle();//角度设置函数
	static const float Width;
	static const float Height;
	float angle=0;//偏转角度
	float dx=0; //dx与dy
	float dy=-1;
    sf::Vector2f position_;
	void setvector();//方向设置函数
    void setheadcolor();

private:
	sf::CircleShape shape_;
	sf::RectangleShape rect_;
};
}

#endif