#ifndef H_animation
#define H_animation
#include <vector>
#include <map>
#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Animation
{
	float CurrentFrame,speed;
	vector<IntRect> frames, frames_flip;
	
	string nameTexture;
	bool flip, isPlaying;
public:
	Sprite sprite;
	Animation();
	Animation(Texture &t, float x, float y, float w, float h, int count, float Speed, int step);
	void setFlip(bool Flip){ flip = Flip; }
	void setIsPlaying(bool IsPlaying){ isPlaying = IsPlaying; }
	void tick(float time);
};

class Animation_manager
{
	string CurrentAnim;
	std::map<string, Animation>animList;
public:
	Animation_manager();
	void create(string name,Texture &t, float x, float y, float w, float h, int count, float Speed, int step);
	void draw(RenderWindow &window, float x, float y);
	void setAnim(string name){ CurrentAnim = name; }
	void flip(bool Flip){ animList[CurrentAnim].setFlip(Flip); }
	void tick(float time){ animList[CurrentAnim].tick(time); }
	void play(){ animList[CurrentAnim].setIsPlaying(true); }
};
#endif