#include "Bullet.h"

Bullet::Bullet() :Parent(){
	CurrentFrame = 0.0;
	x = 0;
	y = 0;
	dir = 0;
	speed = 0;
	dx = 0;
	dy = 0; 
	name_file = "";
	width = 0;
	height = 0;
}

Bullet::Bullet(const double X, const double Y, const double Width, const double Height, const int direction, Level &level, Texture &t) :Parent(X, Y, Width, Height){
	obj = level.GetAllObjects();
	dir = 0;
	CurrentFrame = 0.0;
	x = X;
	y = Y;
	width = 30;
	height = 3;
	speed = 0;
	dx = 0;
	dy = 0;
	dir = direction;
	life = true;
	sprite.setTexture(t);
	sprite.setTextureRect(IntRect(86, 19, 30, 3));
	sprite.setPosition(x, y);
}

void Bullet::move(){
	if ((x > 4320) || (x < 0) || (y > 1760) || (y < 0)){ life = false; }
	if (life){
		if (dir == 0){  speed = 0.5; sprite.setTextureRect(IntRect(86, 19, 30, 3)); sprite.setScale(1.f, 1.f); }//right
		if (dir == 1){  speed = 0.5; sprite.setTextureRect(IntRect(86, 19, 30, 3)); sprite.setScale(-1.f, 1.f); }//left
		if (dir == 2){  speed = 0.5; sprite.setTextureRect(IntRect(19, 4, 3, 30)); sprite.setScale(1.f, -1.f); }//up
		if (dir == 3){  speed = 0.5; sprite.setTextureRect(IntRect(19, 4, 3, 30)); sprite.setScale(1.f, 1.f); }//down
	}
	
}

void Bullet::update(double time){
	move();
	switch (dir){
	case 0: dx = speed; dy = 0; break;
	case 1: dx = -speed; dy = 0; break;
	case 2: dx = 0; dy = speed; break;
	case 3: dx = 0; dy = -speed; break;
	}
	x += dx*time;
	y += dy*time;
	speed = 0;
	sprite.setPosition(x + width / 2, y + height / 2);
	for (int i = 0; i < obj.size(); i++){
		if (getRect().intersects(obj[i].rect)){
			if ((obj[i].name == "Wall") || (obj[i].name == "Jungle") || (obj[i].name == "Barier")){ life = false; }
		}
	}
}
void bulletsCreate(Player &player,list<Bullet*> &bullets,double bulletWidth, double bulletHeight,Level &level,Texture &texture){
	if (player.getIsShoot()){
		player.setIsShoot(false);
		bullets.push_back(new Bullet(player.getX() + 15, player.getY() + 15, bulletWidth, bulletHeight, player.getDir(), level, texture));
	}
}
void bulletsUpdate(list<Bullet*>::iterator bt, list<Bullet*> &bullets, double time){
	for (bt = bullets.begin(); bt != bullets.end();){
		(*bt)->update(time);
		if ((*bt)->getLife() == false){ bt = bullets.erase(bt); }
		else bt++;
	}
}
void bulletsDraw(list<Bullet*>::iterator bt, list<Bullet*> &bullets, RenderWindow &window){
	for (bt = bullets.begin(); bt != bullets.end(); bt++){ window.draw((*bt)->getSprite()); }
}