#ifndef H_player
#define H_player
#include "Parent.h"
class Player: public Parent{
private:
	int heroHealth, heroLifes,heroScore, heroBullets;
	vector<Object>obj;
	bool isShoot;
public:
	Player();
	Player(const double spritePositionX, const double spritePositionY, const double spriteWidth, 
		const double spriteHeight,const string name,Level &level, const string spriteNamefile);
	Player(const Player &player);
	const int getHeroScore(){ return heroScore; }
	const int getHeroHealth(){ return heroHealth; }
	const int getHeroLifes(){ return heroLifes; }
	const int getHeroBullets(){ return heroBullets; }
	const bool getIsShoot(){ return isShoot; }
	void setHeroLifes(const int HeroLifes){ heroLifes = HeroLifes; }
	void setHeroHealth(const int HeroHealth){ heroHealth = HeroHealth; }
	void setHeroScore(const int HeroScore){ heroScore = HeroScore; }
	void setHeroBullets(const int HeroBullets){ heroBullets = HeroBullets; }
	void setIsShoot(const bool IsShoot){ isShoot = IsShoot; }
private:
	ostringstream heroHealthString();
	ostringstream heroLifesString();
	ostringstream heroBulletsString();
	ostringstream heroScoreString();
	ostringstream gameString(int GameTime);
public:
	void resetHeroScore();
	void move(double time);
	void update(double time,Sound &sound);
	void gameActive();
	Text HeroScore(Text &text);
	void showEnd(RenderWindow &window,Text &text,View &view,Texture texture);//
	void showStats(RenderWindow &window, Text &text, View &view,int GameTime);
	void gameOver(RenderWindow &window, Text &text, View &view, int GameTime);
	void attack(double time, Sound &sound, Event event);//
	void teleport(Level &lvl,int levelIndex);
	void SetColor(Color color){ sprite.setColor(color); }
	void interactionBarier(Vertex *line,double time);
	void interactionMap();
	void DirectionDependence(int counter, double time);
	void Intersection(Vertex *line, double x_start, double y_start, double x_end, double y_end, double time);
	~Player(){}
};
double FindAngel(double x_start, double y_start, double x_end, double y_end);
#endif