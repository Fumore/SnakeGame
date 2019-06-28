#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SnakeNode.h"
#include <math.h>
#include <iostream>
using namespace sfSnake;

const float SnakeNode::Width = 10.f;
const float SnakeNode::Height = 10.f;

SnakeNode::SnakeNode(sf::Vector2f position)
: position_(position)
{  
   /* int i=0,j=0;
    sf::Uint8 p[400];
	for (i=0;i<2*SnakeNode::Height/5;i++)
	{
		for (j=0;j<SnakeNode::Width;j++)
		{
			p[4*(10*i+j)]=0;p[4*(10*i+j)+1]=255;p[4*(10*i+j)+2]=0;p[4*(10*i+j)+3]=255;
		}	
	}
	for (i=4;i<6;i++)
	{
		for (j=0;j<SnakeNode::Width;j++)
		{
			p[4*(10*i+j)]=255;p[4*(10*i+j)+1]=255;p[4*(10*i+j)+2]=255;p[4*(10*i+j)+3]=255;
		}	
	}
	for (i=6;i<10;i++)
	{
		for (j=0;j<SnakeNode::Width;j++)
		{
			p[4*(10*i+j)]=0;p[4*(10*i+j)+1]=255;p[4*(10*i+j)+2]=0;p[4*(10*i+j)+3]=255;
		}	
	}
     sf::Texture t;
	 sf::Image image;
	 image.create(10,10,p);
	 t.loadFromImage(image);*/
    shape_.setRadius(0.5*SnakeNode::Height);
    //if (t.loadFromFile("Image/text.JPG"))
	//shape_.setTexture(&t);
	//shape_.setTextureRect(sf::IntRect(0,0,10,10));
	//else
	
	shape_.setFillColor(sf::Color::White);
	shape_.setPosition(position_);
	//shape_.setSize(sf::Vector2f(SnakeNode::Width,SnakeNode::Height));
	shape_.setOutlineColor(sf::Color::Green);
	shape_.setOutlineThickness(-1.f);
	shape_.setOrigin(0.5*SnakeNode::Height,0.5*SnakeNode::Width);
	shape_.setScale(1.3,1.3);
	rect_.setScale(1.3,1.3);

	rect_.setSize(sf::Vector2f(10,2));
	rect_.setFillColor(sf::Color::Green);
	rect_.setOrigin(5,1);
	rect_.setPosition(position_);

}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
	rect_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
	rect_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
	rect_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
	window.draw(rect_);
}

void SnakeNode::setangle()//通过dxdy得到旋转角度
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
	shape_.setRotation(angle);
	rect_.setRotation(angle);
}
void SnakeNode::setheadcolor()
{
	shape_.setFillColor(sf::Color::Green);
}
void SnakeNode::setvector()
{   float i=57.3;
    if (angle>180)
      angle=angle-360;
	if (angle<-180)
	  angle=angle+360;//保持angle在-180到180之间 
	if (angle==0)
	{dx=0;dy=-1;}
	else if (angle==180)
	{dx=0;dy=1;}
	else if (angle==90)
	{dx=1;dy=0;}
	else if (angle==-90)
	{dx=-1;dy=0;}
	else if (angle>0&&angle<90)
	{dx=sin(angle/i);dy=-cos(angle/i);}
	else if (angle<0&&angle>-90)
	{dx=-sin(-angle/i);dy=-cos(-angle/i);}
	else if (angle>90&&angle<180)
	{dx=cos((angle-90)/i);dy=sin((angle-90)/i);}
	else if (angle>-180&&angle<-90)
	{dx=-sin((angle+180)/i);dy=cos((angle+180)/i);}
}

void SnakeNode::firstrender(sf::RenderWindow& window,SnakeNode head)
{
	////
	float t=2;
	angle=angle-head.angle;
	float a=head.angle/57.3;
	shape_.setRotation(angle);
	rect_.setRotation(angle);
	/*float x=position_.x-head.getPosition().x;
	float y=position_.y-head.getPosition().y;
	float x_=x*cos(a)+y*sin(a);
	float y_=-x*sin(a)+y*cos(a);
	setPosition(t*x_,t*y_);
	move(Game::Width / 2,Game::Height / 2);
	window.draw(shape_);
	window.draw(rect_);*/
	shape_.setScale(1.3*t,1.3*t);
	rect_.setScale(1.3*t,1.3*t);
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
	        window.draw(rect_);
		}
	}


}