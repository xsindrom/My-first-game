#ifndef H_parent
#define H_parent
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "level.h"
using namespace std;
using namespace sf;
class Parent
{
protected:
	double x, y, width, height, speed, dx, dy, CurrentFrame;
	int dir;
	string name_file, Name;
	Texture texture;
	Sprite sprite;
	vector<Object>obj;
public:
	Parent();
	Parent(const double spritePositionX, const double spritePositionY,const double spriteWidth, const double spriteHeight,const string textureName,const string name);
	Parent(const double spritePositionX, const double spritePositionY, const double spriteWidth, const double spriteHeight);
	const double getX(){ return x; }
	const double getY(){ return y; }
	const double getWidth(){ return width; }
	const double getHeight(){ return height; }
	const double getSpeed(){ return speed; }
	const double getCurrentFrame(){ return CurrentFrame; }
	const string getName(){ return Name; }
	const int getDir(){ return dir; }
	const string getNameFile(){ return name_file; }
	FloatRect getRect(){ return FloatRect(x, y, width*sprite.getScale().x, height*sprite.getScale().y); }
	Sprite getSprite(){ return sprite; }
	void setSprite(Sprite sp){ sprite = sp; }
	void setX(const double x_){ x = x_; }
	void setY(const double y_){ y = y_; }
	void setWidth(const double width_){ width = width_; }
	void setHeight(const double height_){ height = height_; }
	void setSpeed(const double speed_){ speed = speed_; }
	void setNameFile(const string name){ name_file = name; }
	void setName(const string name){ Name = name; }
};
#endif