#include "Parent.h"
Parent::Parent(){
	x = 0.0;
	y = 0.0;
	width = 0.0;
	height = 0.0;
	dx = 0.0;
	dy = 0.0;
	speed = 0.0;
	dir = 0;
	CurrentFrame = 0.0;
	Name = "";
}

Parent::Parent(const double x_, const double y_,  const double width_, const double height_,const string TextureName, const string name){
	x = x_;
	y = y_;
	width = width_;
	height = height_;
	name_file = TextureName;
	Name = name;
	if (!texture.loadFromFile(name_file)){ return; }
	sprite.setTexture(texture);
	sprite.setOrigin(width / 2, height / 2);
}
Parent::Parent(const double x_, const double y_, const double width_, const double height_){
	x = x_;
	y = y_;
	width = width_;
	height = height_;
}