#ifndef h_menu
#define h_menu
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
void menu(RenderWindow &window,View view)
{
	view.reset(FloatRect(0, 0, 1366, 768));
	window.setView(view);
	Image menu_background_image,menu_background_About_image;
	menu_background_image.loadFromFile("images\\menu\\menu_3.png");
	menu_background_image.createMaskFromColor(Color(0, 0, 0));
	menu_background_About_image.loadFromFile("images\\menu\\Menu_about.png");
	menu_background_About_image.createMaskFromColor(Color(0, 0, 0));

	Texture menu_background_texture;
	Texture menu_button_NG_texture;
	Texture menu_button_Quit_texture;
	Texture menu_button_About_texture;
	Texture menu_background_About_texture;
	menu_background_texture.loadFromImage(menu_background_image);
	menu_background_About_texture.loadFromImage(menu_background_About_image);
	menu_button_NG_texture.loadFromFile("images\\menu\\Button_New_Game.png");
	menu_button_Quit_texture.loadFromFile("images\\menu\\Button_Quit.png");
	menu_button_About_texture.loadFromFile("images\\menu\\Button_About.png");
	Sprite menu_background_sprite(menu_background_texture);
	Sprite menu_button_NG_sprite(menu_button_NG_texture);
	Sprite menu_button_Quit_sprite(menu_button_Quit_texture);
	Sprite menu_button_About_sprite(menu_button_About_texture);
	Sprite menu_background_About_sprite(menu_background_About_texture);
	menu_button_NG_sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	menu_button_About_sprite.setPosition(menu_button_NG_sprite.getPosition().x, menu_button_NG_sprite.getPosition().y + 55);
	menu_button_Quit_sprite.setPosition(menu_button_NG_sprite.getPosition().x, menu_button_NG_sprite.getPosition().y + 110);
	
	bool isMenu = true, show_about = false;
	int Menu_point = 0;

	while (isMenu)
	{
		window.clear(Color(4,41,48));
		Menu_point = 0;

		menu_button_NG_sprite.setColor(Color(255, 255, 255));
		menu_button_About_sprite.setColor(Color(255, 255, 255));
		menu_button_Quit_sprite.setColor(Color(255, 255, 255));
		if (IntRect(menu_button_NG_sprite.getPosition().x, menu_button_NG_sprite.getPosition().y,
			menu_button_NG_texture.getSize().x, menu_button_NG_texture.getSize().y).contains(Mouse::getPosition(window)))
		{
			menu_button_NG_sprite.setColor(Color(0, 191, 255)); Menu_point = 1;
		}
		if (IntRect(menu_button_About_sprite.getPosition().x, menu_button_About_sprite.getPosition().y,
			menu_button_About_texture.getSize().x, menu_button_About_texture.getSize().y).contains(Mouse::getPosition(window)))
		{
			menu_button_About_sprite.setColor(Color(0, 191, 255)); Menu_point = 2;
		}
		if (IntRect(menu_button_Quit_sprite.getPosition().x, menu_button_Quit_sprite.getPosition().y,
			menu_button_Quit_texture.getSize().x, menu_button_Quit_texture.getSize().y).contains(Mouse::getPosition(window)))
		{
			menu_button_Quit_sprite.setColor(Color(0, 191, 255)); Menu_point = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Menu_point == 1){ isMenu = false; }
			if (Menu_point == 2){ show_about = true; }
			if (Menu_point == 3){ exit(0);}
		}
		if (Mouse::isButtonPressed(Mouse::Right)){ show_about = false; }
		window.draw(menu_background_sprite);
		window.draw(menu_button_NG_sprite);
		window.draw(menu_button_About_sprite);
		window.draw(menu_button_Quit_sprite);
		if (show_about){ window.draw(menu_background_About_sprite); }
		window.display();
	}
}

#endif