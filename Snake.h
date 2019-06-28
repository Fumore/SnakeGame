#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"
#include "BadNode.h"
namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down
	};

class Snake
{
public:
	Snake();
    int lattice=-1;//判断是否要添加网格
	void handleInput(sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);
    void latticerender(sf::RenderWindow& window);//添加网格函数
	void checkFruitCollisions(std::vector<Fruit>& fruits);
    int back=1;//判断背景
	void backrender(sf::RenderWindow& window,int b);//背景绘制函数
	bool hitSelf() const;
    int Bad=-1;//判断是否加入敌方
	unsigned getSize() const;
    void initBadNodes();//初始化敌方
	int f=-1;//判断是否用第一人称
	SnakeNode re();
private:
	void move(sf::Time delta);
	void grow();
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();
    

	bool hitSelf_;

	sf::Vector2f position_;
	Direction direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;
    std::vector<BadNode> badnodes_;//敌方容器
	static const int InitialSize;
};
}

#endif