#ifndef h_bullet
#define h_bullet
#include "Player.h"
#include <list>
class Bullet : public Parent
{
	bool life;
public:
	Bullet();
	Bullet(const double spritePositionX, const double spritePositionY,const double spriteWidth,const double spriteHeight,
		const int direction, Level &level, Texture &t);
	const bool getLife(){ return life; }
	void setLife(const bool l){ life = l; }
	void move();
	void update(double time);
};
void bulletsCreate(Player &player, list<Bullet*> &bullets, double bulletWidth, double bulletHeight, Level &level, Texture &texture);
void bulletsUpdate(list<Bullet*>::iterator bt, list<Bullet*> &bullets, double time);
void bulletsDraw(list<Bullet*>::iterator bt, list<Bullet*> &bullets, RenderWindow &window);
#endif