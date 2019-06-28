#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include<math.h>
#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "BadNode.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
{
	initNodes();
    initBadNodes();
	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}
SnakeNode  Snake::re()
{
	return nodes_[0];
}
void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
	}
	nodes_[0].setheadcolor();
}
void Snake::initBadNodes()//初始化敌方函数
{
	
		for (int i = 0; i < Snake::InitialSize; ++i)
		badnodes_.push_back(BadNode(sf::Vector2f(Game::Width *1.1,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height *5*i))));
	
}

void Snake::handleInput(sf::RenderWindow& window)
{       
		 if (sf::Mouse::isButtonPressed( sf::Mouse::Left)&&f<0)//鼠标事件
		 {
            float x=sf::Mouse::getPosition(window).x-nodes_[0].position_.x;
			float y=sf::Mouse::getPosition(window).y-nodes_[0].position_.y;
			float r=sqrt(x*x+y*y);
			if (r)
			{
			nodes_[0].dx=x/r;
			nodes_[0].dy=y/r;
			}  
		 } 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&f<0)
		{direction_ = Direction::Up;nodes_[0].dx=0;nodes_[0].dy=-1;}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&f<0)
		{direction_ = Direction::Down;nodes_[0].dx=0;nodes_[0].dy=1;}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&f<0)
		{direction_ = Direction::Left;nodes_[0].dx=-1;nodes_[0].dy=0;}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&f<0)
		{direction_ = Direction::Right;nodes_[0].dx=1;nodes_[0].dy=0;}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		lattice=lattice*(-1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		back=1;	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		back=2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		back=3;		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		Game::setspeedup();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		Game::setspeeddown();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))//B键设置是否有敌方
		Bad=Bad*(-1);

		float w=10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//AD控制法
		{nodes_[0].angle=nodes_[0].angle-w;nodes_[0].setvector();}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{nodes_[0].angle=nodes_[0].angle+w;nodes_[0].setvector();}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))//控制第一人称
		{f=-f;}
}

void Snake::update(sf::Time delta)
{
	move(delta);
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		if (toRemove->k==1)
		{grow();grow();grow();}
		if (toRemove->k==2)
		{
			grow();grow();
		}
		if (toRemove->k==3)
		 grow();
		fruits.erase(toRemove);
	}
}

void Snake::grow()
{
	switch (direction_)
	{
	case Direction::Up:
		nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
			nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));
		break;
	case Direction::Down:
		nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
			nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height)));
		break;
	case Direction::Left:
		nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width,
			nodes_[nodes_.size() - 1].getPosition().y)));
		break;
	case Direction::Right:
		nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width,
			nodes_[nodes_.size() - 1].getPosition().y)));
		break;
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 4; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
	if (Bad>0)
	{
		for (auto& badnode:badnodes_)
	{
		if (headNode.getBounds().intersects(badnode.getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
	}
	
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move(sf::Time delta)
{   int v=30;
    int j=0;
    float t=delta.asSeconds();
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
		nodes_[i].dx=nodes_[i-1].dx;
		nodes_[i].dy=nodes_[i-1].dy;
		nodes_[i].setangle();
	}
    nodes_[0].move(nodes_[0].dx*SnakeNode::Height,nodes_[0].dy*SnakeNode::Height);
	nodes_[0].setangle();
    if (Bad>0)//敌方移动
	{
      for (auto& badnode:badnodes_)
	  {   j++;
		  float x=nodes_[0].position_.x-badnode.position_.x;
		  float y=nodes_[0].position_.y-badnode.position_.y;
          float r=sqrt(x*x+y*y);
			if (r)
			{
			badnode.dx=x/r;
			badnode.dy=y/r;
			} 
			badnode.move(badnode.dx*v*t*j,badnode.dy*v*t*j);
			badnode.setangle();
	  }
	}

	/*switch (direction_)
	{
	case Direction::Up:
		nodes_[0].move(0, -SnakeNode::Height);
		break;
	case Direction::Down:
		nodes_[0].move(0, SnakeNode::Height);
		break;
	case Direction::Left:
		nodes_[0].move(-SnakeNode::Width, 0);
		break;
	case Direction::Right:
		nodes_[0].move(SnakeNode::Width, 0);
		break;
	}*/
}

void Snake::render(sf::RenderWindow& window)
{ if (f<0)
 {
    for (auto node : nodes_)
		node.render(window);
	if (Bad>0)//绘制敌方
	{
		for (auto badnode : badnodes_)
		{badnode.render(window);}
	}
 }
 if (f>0)
   {
	   for (auto node : nodes_)
		node.firstrender(window,nodes_[0]);
	if (Bad>0)//绘制敌方
	{
		for (auto badnode : badnodes_)
		{badnode.firstrender(window,nodes_[0]);}
	}	
   }
	
}
void Snake::latticerender(sf::RenderWindow& window)//网格绘制函数
{
    sf::RectangleShape hline(sf::Vector2f(Game::Width,1));
	hline.setFillColor(sf::Color::Blue);
	for (int i=0;i<Game::Height/10;i++)
	{
		hline.setPosition(sf::Vector2f(0,i*10));
		window.draw(hline);
	}
	sf::RectangleShape sline(sf::Vector2f(1,Game::Height));
	sline.setFillColor(sf::Color::Blue);
	for (int j=0;j<Game::Width/10;j++)
	{
		sline.setPosition(sf::Vector2f(j*10,0));
		window.draw(sline);
	}
}
void Snake::backrender(sf::RenderWindow& window,int b)//背景绘制函数
{
	sf::RectangleShape picture(sf::Vector2f(Game::Width,Game::Height));
	const sf::Color q{77,26,107};
    const sf::Color w{255,255,255};
	const sf::Color e{0,0,0};
	if (b==1)
	picture.setFillColor(q);
	if (b==2)
	picture.setFillColor(w);
	if (b==3)
	picture.setFillColor(e);
	window.draw(picture);
}