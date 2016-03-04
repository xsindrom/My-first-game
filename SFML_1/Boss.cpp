#include "Boss.h"

Boss::Boss(){
	CurrentFrame = 0.0;
	x = 0.0;
	y = 0.0;
	width = 0.0;
	height = 0.0;
	speed = 0.0;
	dx = 0.0;
	dy = 0.0;
	isLife = true;
	isMove = true;
	isAttacked = false;
	enemyHealth = 0;
	name_file = "";
	Name = "";
}
Boss::Boss(const double X, const double Y, const double Width, const double Height, const string NM, const string name){
	x = X;
	y = Y;
	width = Width;
	height = Height;
	name_file = "images\\boss\\" + NM;
	Name = name;
	enemyHealth = 1000;
	isLife = true;
	isMove = true;
	isAttacked = false;
	if (!texture.loadFromFile(name_file)){ return; }
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(12, 10, width, height));
	sprite.setPosition(x, y);
	sprite.setScale(4.0f, 4.0f);
	sprite.setOrigin(width / 2, height / 2);
}
Boss::Boss(const Boss &boss){
	x = boss.x;
	y = boss.y;
	width = boss.width;
	height = boss.height;
	name_file = boss.name_file;
	Name = boss.Name;
	enemyHealth = 1000;
	isLife = boss.isLife;
	isMove = boss.isMove;
	isAttacked = boss.isAttacked;
	if (!texture.loadFromFile(name_file)){ return; }
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(12, 10, width, height));
	sprite.setPosition(x, y);
	sprite.setScale(4.0f, 4.0f);
	sprite.setOrigin(width / 2, height / 2);
}
void Boss::update(double time){
	if (enemyHealth <= 0){
		CurrentFrameOff += 0.0008*time;
		sprite.setTextureRect(IntRect(154, int(CurrentFrameOff) * 72 + 658, width + 10, height));
		if (CurrentFrameOff > 4.5){ isLife = false; }
	}
}
void bossUpdate(list<Boss*>::iterator bt, list<Boss*>boss, double time) {
	for (bt = boss.begin(); bt != boss.end(); bt++){ (*bt)->update(time); }
}
void bossDraw(list<Boss*>::iterator bt, list<Boss*>boss, RenderWindow &window){
	for (bt = boss.begin(); bt != boss.end(); bt++){ window.draw((*bt)->getSprite()); }
}
void bossPlayerDetection(list<Boss*>::iterator bt, list<Boss*>boss, Player &player, double time, Sound &sound){
	for (bt = boss.begin(); bt != boss.end(); bt++){
		(*bt)->playerDetection(player, time, sound);
	}
}
void bossShowStats(list<Boss*>::iterator bt, list<Boss*>boss, RenderWindow &window, Text &text){
	for (bt = boss.begin(); bt != boss.end(); bt++){
		(*bt)->showStats(window, text);
	}
}
void bossInteractionBullets(list<Boss*>::iterator Bt, list<Boss*>&boss, list<Bullet*>::iterator bt, list<Bullet*> &bullets, double time){
	for (Bt = boss.begin(); Bt != boss.end();)
	{
		for (bt = bullets.begin(); bt != bullets.end(); bt++){
			(*Bt)->kill((*bt), time);
		}
		if ((*Bt)->getIsLife() == false){
			Bt = boss.erase(Bt);
		}
		else Bt++;
	}
}
bool bossDead(list<Boss*>::iterator Bt, list<Boss*>boss){
	for (Bt = boss.begin(); Bt != boss.end(); Bt++){
		if ((*Bt)->getIsLife() == false){ return true; }
		else return false;
	}
}
