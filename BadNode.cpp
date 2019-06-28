#include <SFML/Graphics.hpp>

#include "BadNode.h"
#include "SnakeNode.h"
#include "Game.h"
#include <math.h>
#include <iostream>
using namespace sfSnake;

const float BadNode::Width = 10.f;
const float BadNode::Height = 10.f;

BadNode::BadNode(sf::Vector2f position)
: position_(position)
{  
   
	tri.setPointCount(3);
	tri.setPoint(0,sf::Vector2f(10,0));
	tri.setPoint(1,sf::Vector2f(0,10));
	tri.setPoint(2,sf::Vector2f(20,10));
    tri.setFillColor(sf::Color::Red);
    tri.setOrigin(10,5);
	tri.setOutlineThickness(-1.f);
	tri.setOutlineColor(sf::Color::Blue);
	tri.setPosition(position_);
}

void BadNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	tri.setPosition(position_);
	
}

void BadNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	tri.setPosition(position_);
	
}

void BadNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	tri.setPosition(position_);
	
}

sf::FloatRect BadNode::getBounds() const
{
	return tri.getGlobalBounds();
}

sf::Vector2f BadNode::getPosition() const
{
	return position_;
}

void BadNode::render(sf::RenderWindow& window)
{
	window.draw(tri);
	
}
void BadNode::firstrender(sf::RenderWindow& window,SnakeNode head)
{
	////
	float t=2;
	angle=angle-head.angle;
	float a=head.angle/57.3;
	tri.setRotation(angle);
	/*float x=position_.x-head.getPosition().x;
	float y=position_.y-head.getPosition().y;
	float x_=x*cos(a)+y*sin(a);
	float y_=-x*sin(a)+y*cos(a);
	setPosition(t*x_,t*y_);
	move(Game::Width / 2,Game::Height / 2);
	window.draw(shape_);
	window.draw(rect_);*/
	tri.setScale(t,t);

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
			window.draw(tri);
		}
	}


}
void BadNode::setangle()//通过dxdy得到旋转角度
{   float i=57.3;
    if (dx==0&&dy==-1)
	{angle=0;}
	else if (dx==0&&dy==1)
	{angle=180;}
	else if (dx==-1&&dy==0)
	{angle=-90;}
	else if (dx==1&&dy==0)
	{angle=90;}
	else if (dx>0&&dy>0)
	{angle=90+i*atan(dy/dx);}
	else if (dx>0&&dy<0)
	{angle=90-i*atan(-dy/dx);}
	else if (dx<0&&dy>0)
	{angle=-90-i*atan(-dy/dx);}
	else if (dx<0&&dy<0)
	{angle=-90+i*atan(dy/dx);}
	tri.setRotation(angle);
	
}
