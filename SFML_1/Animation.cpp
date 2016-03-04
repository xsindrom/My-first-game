#include "Animation.h"
Animation::Animation()
{
	speed = 0.0;
	CurrentFrame = 0.0;
	flip = false;
	isPlaying = true;
	nameTexture = "";

}
Animation::Animation(Texture &t, float x, float y, float w, float h, int count, float Speed, int step)
{
	speed = Speed;
	sprite.setTexture(t);

	CurrentFrame = 0.0;
	flip = false;
	isPlaying = true;
	for (int i = 0; i < count; i++)
	{
		frames.push_back(IntRect(x, y + i*step, w, h));
		frames_flip.push_back(IntRect(x, y + i*step + h, -w, h));
	}
}
void Animation::tick(float time)
{
	if (!isPlaying){ return; }
	CurrentFrame += time*speed;

	if (CurrentFrame > frames.size()){ CurrentFrame -= frames.size(); }

	int i = CurrentFrame;
	sprite.setTextureRect(frames[i]);
	if (flip){ sprite.setTextureRect(frames_flip[i]); }
}

Animation_manager::Animation_manager(){}
void Animation_manager::create(string name,Texture &t, float x, float y, float w, float h, int count, float Speed, int step)
{
	animList[name] = Animation(t, x, y, w, h, count, Speed, step);
	CurrentAnim = name;
}

void Animation_manager::draw(RenderWindow &window, float x, float y)
{
	animList[CurrentAnim].sprite.setPosition(x, y);
	window.draw(animList[CurrentAnim].sprite);
}