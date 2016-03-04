#ifndef H_enemy
#define H_enemy
#include "Bullet.h"
class Enemy: public Parent{
private:
	SoundBuffer soundBuffer;
	double horizontal_start_fence, vertical_start_fence, horizontal_end_fence, vertical_end_fence;
protected:
	double CurrentFrameOff;
	int enemyHealth;
	bool isLife, isAttacked,isMove;
public:
	Enemy();
	Enemy(const double sprite_position_x, const double sprite_position_y, const double sprite_width,
		const double sprite_height,const string Name,Level &level, const string sprite_name_of_file);
	Enemy(const double sprite_position_x, const double sprite_position_y, const double sprite_width,
		const double sprite_height, const double vsf,const double vef,
		const double hsf, const double hef, const string Name,Level &level, const string sprite_name_of_file);
	Enemy(const Enemy &enemy);
	const double getHorizontalStartFence(){ return horizontal_start_fence; }
	const double getHorizontalEndFence(){ return horizontal_end_fence; }
	const double getVerticalStartFence(){ return vertical_start_fence; }
	const double getVerticalEndFence(){ return vertical_end_fence; }
	const int getEnemyHealth(){ return enemyHealth; }
	const bool getIsLife(){ return isLife; }
	void setIsLife(const bool Life){ isLife = Life; }
private:
	ostringstream getEnemyHealthString();
public:
	virtual void move(double time);
	virtual void interactionPlayer(Player &player,double time,Sound &sound_attack);
	virtual void update(double time, double Vertical_start_fence,
		double Vertical_end_fence, double Horizontal_start_fence,
		double Horizontal_end_fence,  Player &player, Sound &sound_attack);
	virtual void update(double time, Player &player, Sound &sound_attack);
	void kill(Bullet *bullet,double time);
	void playerDetection(Player &player, double time,Sound &sound);
	bool interactionMap(double time, double tan);
	void stay(double time);
	void showStats(RenderWindow &window,Text &text);
	~Enemy(){}
};
void enemiesPlayerDetection(list<Enemy*>::iterator it, list<Enemy*>enemies, Player &player, double time, Sound &sound);
void enemiesInitialize(list<Enemy*>&enemies_horizontal, Level &level,string ObjectName);
void enemiesUpdate(list<Enemy*>::iterator it, list<Enemy*>enemies, Player &player, Sound &sound_attack, double time);
void enemiesShowStats(list<Enemy*>::iterator it, list<Enemy*>enemies, RenderWindow &window, Text &text);
void enemiesDraw(list<Enemy*>::iterator it, list<Enemy*>enemies, RenderWindow &window);
void enemiesInteractionBullets(list<Enemy*>::iterator it, list <Enemy*> &enemies, list<Bullet*>::iterator bt,
	list<Bullet*> &bullets, double time,Player &player);
#endif