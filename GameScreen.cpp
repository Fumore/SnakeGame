#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

    
GameScreen::GameScreen() : snake_()
{
    for (int i=0;i<8;i++)
	generateFruit();//初始化时产生8个水果

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() < 8)
		generateFruit();
   
	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{       
	//更换背景
    snake_.backrender(window,snake_.back);                        
	
	if (snake_.lattice>0)//是否绘制网格
	snake_.latticerender(window);

	snake_.render(window);
    if (snake_.f<0)
	{
		for (auto fruit : fruit_)
		fruit.render(window);
	}
	if (snake_.f>0)
	{
		for (auto fruit : fruit_)
		fruit.firstrender(window,snake_.re());
	}
	
}

void GameScreen::generateFruit()
{   static int i=0;
    i++;
	static std::default_random_engine engine;
	if (i<2)
	engine.seed(time(NULL));//只初始化一次种子

	
    int a=0,b=0;int k;//决定种类
    for (auto fruit:fruit_)
    {
       if (fruit.k<=3) a++;
	   else b++;
    }
	static std::uniform_int_distribution<int> c(1, 3);
	static std::uniform_int_distribution<int> d(4, 5);
	
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);
     if (a<6) k=c(engine);
     else  k=d(engine);
	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),k));
}

