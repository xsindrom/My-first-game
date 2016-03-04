#ifndef h_Missions
#define h_Missions
#include <iostream>

int getNumber_of_misson(int LevelIndex)
{
	int mission = 0;
	if (LevelIndex == 0){ mission = 0; }
	if (LevelIndex == 1){ mission = 1; }
	if (LevelIndex == 2){ mission = 2; }
	if (LevelIndex == 3){ mission = 3; }
	if (LevelIndex == 4){ mission = 4; }
	if (LevelIndex == 5){ mission = 5; }
	if (LevelIndex == 6){ mission = 6; }
	return mission;
}

std::string getText_of_mission(int n)
{
	std::string Mission_task = "";
	switch (n)
	{
	case 0:Mission_task = "Explore the town\n and walk to\n the north\n rune"; break;
	case 1:Mission_task = "Be careful\nget to far\n west rune"; break;
	case 2:Mission_task = "First fight\nfirst blood\nkill ogres"; break;
	case 3:Mission_task = "Try to survive\nand reach\nwest"; break;
	case 4:Mission_task = "Try to not die\nmore peacefull\nogres"; break;
	case 5:Mission_task = "Calm walking\nnothing\n interesting"; break;
	case 6:Mission_task = "You will fail\nyou will\nDIE"; break;
	default: Mission_task = "More kills, more honor"; break;
	}
	return Mission_task;
}

std::ostringstream task_String(int LevelIndex)
{
	std::ostringstream task_string;
	task_string << getText_of_mission(getNumber_of_misson(LevelIndex));
	return task_string;
}
Texture MissionTexture()
{
	Image mission_image;
	mission_image.loadFromFile("images\\mission\\missionbg.jpg");
	mission_image.createMaskFromColor(Color(0, 0, 0));
	Texture mission_texture;
	mission_texture.loadFromImage(mission_image);
	return mission_texture;
}
void Mission_draw(bool showMission_text, Text text, Texture mission_texture, Player player,RenderWindow &window,View &view)
{
	Sprite mission_sprite;
	mission_sprite.setTexture(mission_texture);
	mission_sprite.setTextureRect(IntRect(0, 0, 340, 510));
	mission_sprite.setScale(0.6f*view.getSize().x / window.getSize().x, 0.6f*view.getSize().y / window.getSize().y);
	if (!showMission_text)
	{
		text.setPosition(player.getX() + 130, player.getY() - 120);
		mission_sprite.setPosition(player.getX() + 115, player.getY() - 130);
		window.draw(mission_sprite);
		window.draw(text);
	}
}

void MissionShow(Text &text,Text &text_stats, bool &showMission_text, Event Event_main,int LevelIndex)
{
	if (Event_main.type == Event::KeyPressed)
	{
		if (Event_main.key.code == Keyboard::Tab)
		{
			switch (showMission_text)
			{
			case true:text.setString(task_String(LevelIndex).str()); showMission_text = false; break;
			case false:text.setString(""); showMission_text = true; break;
			}
		}
	}
}
#endif