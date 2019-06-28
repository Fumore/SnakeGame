#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include "SnakeNode.h"
#include "Game.h"
#include <math.h>
using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position,int i)
: k(i),position_(position)
{   
    const sf::Color Brown{139,105,20};
	const sf::Color Black{0,0,0};

	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	if(i==1) 
	shape_.setFillColor(sf::Color::Red);
	if(i==2)
	shape_.setFillColor(sf::Color::Green);
	if(i==3)
	shape_.setFillColor(sf::Color::Blue);
	if(i==4)
    shape_.setFillColor(Black);
	if(i==5)
	shape_.setFillColor(Brown);

	
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}
void Fruit::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}
void Fruit::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
}	

void Fruit::firstrender(sf::RenderWindow& window,SnakeNode head)//第一人称视角
{
	////
	float t=2;
	float a=head.angle/57.3;
	shape_.setScale(t,t);
	float xa=position_.x;float ya=position_.y;
	for (int i=-1;i<2;i++)
	{
		for (int j=-1;j<2;j++)
		{
            float x=xa-head.getPosition().x+i*Game::Width;
			float y=ya-head.getPosition().y+j*Game::Height;
			float x_=x*cos(a)+y*sin(a);
	        float y_=-x*sin(a)+y*cos(a);
			setPosition(t*x_,t*y_);
	        move(Game::Width / 2,Game::Height / 2);
			window.draw(shape_);
	        
		}
	}
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}