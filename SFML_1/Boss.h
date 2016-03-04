#ifndef H_boss
#define H_boss
#include "Enemy.h"
#include "Bullet.h"
class Boss : public Enemy{
public:
	Boss();
	Boss(const double spritePositionX, const double spritePositionY, const double spriteWidth, const double spriteHeight,
		const string nameFile,const string name);
	Boss(const Boss &boss);
	void update(double time);
	~Boss(){};
};
void bossUpdate(list<Boss*>::iterator bt, list<Boss*>boss, double time);
void bossDraw(list<Boss*>::iterator bt, list<Boss*>boss, RenderWindow &window);
void bossPlayerDetection(list<Boss*>::iterator bt, list<Boss*>boss, Player &player, double time, Sound &sound);
void bossInteractionBullets(list<Boss*>::iterator Bt, list<Boss*>&boss, list<Bullet*>::iterator bt, list<Bullet*> &bullets, double time);
void bossShowStats(list<Boss*>::iterator bt, list<Boss*>boss, RenderWindow &window, Text &text);
bool bossDead(list<Boss*>::iterator Bt, list<Boss*>boss);
#endif