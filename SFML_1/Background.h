#ifndef h_Background
#define h_Background
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Background
{
	Texture background_texture;
	Sprite background_sprite;
	string background_name_of_file;
public:
	Background();
	Background(string);
	void setBackground_name_of_file(string);
	string getBackground_name_of_file();
	Texture getBackground_texture();
	Sprite getBackground_sprite();
	void Background_initialize();
};

#endif