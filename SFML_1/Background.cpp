#include "Background.h"
Background::Background(){}
Background::Background(string Bp)
{
	background_name_of_file = Bp;
	if (!background_texture.loadFromFile("images\\" + Bp)){ return; }
	background_sprite.setTexture(background_texture);
	background_sprite.setPosition(0, 0);
}

void Background::setBackground_name_of_file(string NM){ background_name_of_file = NM; }
string Background::getBackground_name_of_file(){ return background_name_of_file; }
Texture Background::getBackground_texture(){ return background_texture; }
Sprite Background::getBackground_sprite(){ return background_sprite; }

void Background::Background_initialize()
{
	string BNF;
	cout << "background_name = ";
	cin >> BNF;
	setBackground_name_of_file("images\\"+BNF);
	if (!background_texture.loadFromFile(getBackground_name_of_file())){ return; }
	background_sprite.setTexture(background_texture);
	background_sprite.setPosition(-30, -20);
}
