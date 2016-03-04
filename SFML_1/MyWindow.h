#ifndef H_MyWindow
#define H_MyWindow
#include "Camera.h"
#include "Background.h"
#include "Missions.h"
#include "Menu.h"
#include "Boss.h"
#include "Bullet.h"
#include <list>

class My_Window
{
private:
	RenderWindow Window_main;
	Event Event_main;
	double time;
	Vector2i CursorPositionPixel;
	int levelIndex, level_count;
private:
	Font chooseFont(int number_of_font){
		Font font;
		if (number_of_font == 1){ font.loadFromFile("Fonts\\Tahoma-regular.ttf"); }
		if (number_of_font == 2){ font.loadFromFile("Fonts\\Monotype-Corsiva-Regular.ttf"); }
		return font;
	}
	void CloseWindow(){
		if (Event_main.type == Event_main.Closed){ Window_main.close(); }
	}
	void Work_with_Camera(View &view){
		view.reset(FloatRect(0, 0, 1366, 768));
	}

	void scrollingMap(){
		if (Mouse::isButtonPressed(Mouse::Left)){
			Window_main.setView(viewOff);
			cameraScroll(time, CursorPositionPixel, Window_main.getSize().x, Window_main.getSize().y);
		}
		else{ Window_main.setView(viewMain); }
	}
	void newLevel(Level &level){
		switch (levelIndex){
		case 0: level.LoadFromFile("Level_8_map.tmx"); break;
		case 1: level.LoadFromFile("Level_6_map.tmx"); break;
		case 2: level.LoadFromFile("Level_4_map.tmx"); break;
		case 3: level.LoadFromFile("Level_3_map.tmx"); break;
		case 4: level.LoadFromFile("Level_1_map.tmx"); break;
		case 5: level.LoadFromFile("Level_5_map.tmx"); break;
		case 6: level.LoadFromFile("Level_9_map.tmx"); break;
		default: level.LoadFromFile("Level_8_map.tmx"); break;
		}
	}
	void setMusic(Music &music){
		switch (levelIndex){
		case 0:music.openFromFile("music\\Stormwind_intro-moment.ogg"); break;
		case 1:music.openFromFile("music\\DayJungle03.ogg"); break;
		case 2:music.openFromFile("music\\battle06.ogg"); break;
		case 3:music.openFromFile("music\\battle06.ogg"); break;
		case 4:music.openFromFile("music\\battle06.ogg"); break;
		case 5:music.openFromFile("music\\battle06.ogg"); break;
		case 6:music.openFromFile("music\\battle06.ogg"); break;
		default: break;
		}
	}
public:
	My_Window(){
		Window_main.create(VideoMode(1366, 768), "My window class", Style::Close|Style::Fullscreen);
		Window_main.setPosition(Vector2i(0, 0));
		Window_main.setFramerateLimit(100);
		menu(Window_main, viewMain);
		levelIndex = 0;
	}
	
	bool mainWindow(int &level_index){
		Level level;
		newLevel(level);
		Object p = level.GetObject("Player");
		Player player(p.rect.left, p.rect.top, 50.0, 55.0, "Dima", level, "elven_archer.png");
		player.setHeroBullets(100);
		Boss *BOSS;
		if (levelIndex == 6){
			Object b = level.GetObject("Boss");
			BOSS = new Boss(b.rect.left, b.rect.top, 55.0, 55.0, "death_knight.png", "Arthas");
		}
		list<Boss*>boss; boss.push_back(BOSS);
		list<Boss*>::iterator Bt;
		list<Enemy*>enemies_horizontalOgre; enemiesInitialize(enemies_horizontalOgre, level, "Enemy_horizontalOgre");
		list<Enemy*>enemies_verticalOgre; enemiesInitialize(enemies_verticalOgre, level, "Enemy_verticalOgre");
		list<Enemy*>enemies_horizontalGrunt; enemiesInitialize(enemies_horizontalGrunt, level, "Enemy_horizontalGrunt");
		list<Enemy*>enemies_verticalGrunt; enemiesInitialize(enemies_verticalGrunt, level, "Enemy_verticalGrunt");
		list<Enemy*>enemies_horizontalPeon; enemiesInitialize(enemies_horizontalPeon, level, "Enemy_horizontalPeon");
		list<Enemy*>enemies_verticalPeon; enemiesInitialize(enemies_verticalPeon, level, "Enemy_verticalPeon");
		list<Enemy*>::iterator it;
		list<Bullet*> bullets;
		list<Bullet*>::iterator bt;

		Texture texture; texture.loadFromFile("images\\Other_texture\\arrow.png");
		Work_with_Camera(viewMain); Work_with_Camera(viewOff);


		SoundBuffer enemy_soundbuf, player_soundbuf;
		if (!enemy_soundbuf.loadFromFile("sound\\FallingDamageA.wav")){ cout << "file didn't loaded" << endl; }
		if (!player_soundbuf.loadFromFile("sound\\GunFire01.wav")){ cout << "file didn't loaded" << endl; }
		Sound enemy_sound_attack; enemy_sound_attack.setBuffer(enemy_soundbuf); enemy_sound_attack.setPitch(0.5f); enemy_sound_attack.setVolume(20);
		Sound player_sound_attack; player_sound_attack.setBuffer(player_soundbuf); player_sound_attack.setPitch(0.6f); player_sound_attack.setVolume(20);
		Music music; setMusic(music);
		music.setLoop(true); music.setVolume(100);
		Texture  mission_texture(MissionTexture());
		Font font(chooseFont(2));
		Text text("", font, 20); text.setColor(Color(255, 0, 0));
		Text text_1("", font, 20); text_1.setColor(Color(127, 0, 14));
		Text text_2("", font, 20); text_1.setColor(Color(255, 0, 0));
		Clock clock, gameTime; int Game = 0; bool showMission_text = true;
		
		while (Window_main.isOpen()){
			if (Keyboard::isKeyPressed(Keyboard::M)){
				music.play();
			}
			time = clock.getElapsedTime().asMicroseconds() / 400; clock.restart();
			if (Keyboard::isKeyPressed(Keyboard::F2)){ gameTime.restart(); return true; }
			if (Keyboard::isKeyPressed(Keyboard::F1)){ return false; }
			CursorPositionPixel = Mouse::getPosition(Window_main);
		
			if (player.getHeroLifes() > 0){ Game = gameTime.getElapsedTime().asSeconds(); }
			while (Window_main.pollEvent(Event_main)){
				CloseWindow();
				MissionShow(text_1, text, showMission_text, Event_main,levelIndex);
				if (player.getHeroLifes() > 0){
					player.attack(time, player_sound_attack, Event_main);
				}
				bulletsCreate(player, bullets, 30, 3, level, texture);
			}
			scrollingMap();
			cameraLook(player);
			cameraSpecial();
			Window_main.clear(Color(135, 206, 235));
			player.update(time, player_sound_attack);
			enemiesUpdate(it, enemies_horizontalOgre, player, enemy_sound_attack, time);
			enemiesUpdate(it, enemies_verticalOgre, player, enemy_sound_attack, time);
			enemiesUpdate(it, enemies_horizontalGrunt, player, enemy_sound_attack, time);
			enemiesUpdate(it, enemies_verticalGrunt, player, enemy_sound_attack, time);
			enemiesUpdate(it, enemies_horizontalPeon, player, enemy_sound_attack, time);
			enemiesUpdate(it, enemies_verticalPeon, player, enemy_sound_attack, time);
			enemiesPlayerDetection(it, enemies_horizontalOgre, player, time, enemy_sound_attack);
			enemiesPlayerDetection(it, enemies_verticalOgre, player, time, enemy_sound_attack);
			enemiesPlayerDetection(it, enemies_horizontalGrunt, player, time, enemy_sound_attack);
			enemiesPlayerDetection(it, enemies_verticalGrunt, player, time, enemy_sound_attack);
			enemiesPlayerDetection(it, enemies_horizontalPeon, player, time, enemy_sound_attack);
			enemiesPlayerDetection(it, enemies_verticalPeon, player, time, enemy_sound_attack);
			bulletsUpdate(bt, bullets, time);
			enemiesInteractionBullets(it, enemies_horizontalOgre, bt, bullets, time,player);
			enemiesInteractionBullets(it, enemies_verticalOgre, bt, bullets, time, player);
			enemiesInteractionBullets(it, enemies_horizontalGrunt, bt, bullets, time, player);
			enemiesInteractionBullets(it, enemies_verticalGrunt, bt, bullets, time, player);
			enemiesInteractionBullets(it, enemies_horizontalPeon, bt, bullets, time, player);
			enemiesInteractionBullets(it, enemies_verticalPeon, bt, bullets, time, player);
			level.Draw(Window_main);
			player.showStats(Window_main, text, viewMain, Game);
			player.gameOver(Window_main, text, viewMain, Game);
			player.showEnd(Window_main, text, viewMain, mission_texture);
			player.teleport(level, levelIndex);
			Window_main.draw(player.getSprite());
			enemiesShowStats(it, enemies_horizontalOgre, Window_main, text_2);
			enemiesShowStats(it, enemies_verticalOgre, Window_main, text_2);
			enemiesShowStats(it, enemies_horizontalGrunt, Window_main, text_2);
			enemiesShowStats(it, enemies_verticalGrunt, Window_main, text_2);
			enemiesShowStats(it, enemies_horizontalPeon, Window_main, text_2);
			enemiesShowStats(it, enemies_verticalPeon, Window_main, text_2);
			enemiesDraw(it, enemies_horizontalOgre, Window_main);
			enemiesDraw(it, enemies_verticalOgre, Window_main);
			enemiesDraw(it, enemies_horizontalGrunt, Window_main);
			enemiesDraw(it, enemies_verticalGrunt, Window_main);
			enemiesDraw(it, enemies_horizontalPeon, Window_main);
			enemiesDraw(it, enemies_verticalPeon, Window_main);
			bulletsDraw(bt, bullets, Window_main);
			Mission_draw(showMission_text, text_1, mission_texture, player, Window_main, viewMain);
			if (levelIndex == 6){
				bossPlayerDetection(Bt, boss, player, time, enemy_sound_attack);
				bossUpdate(Bt, boss, time);
				bossInteractionBullets(Bt, boss, bt, bullets, time);
				bossShowStats(Bt, boss, Window_main, text_2);
				bossDraw(Bt, boss, Window_main);
				if (bossDead(Bt, boss)){ menu(Window_main, viewMain); }
			}
			Window_main.display();
			if (Keyboard::isKeyPressed(Keyboard::F3)){
				if (player.getRect().intersects(level.GetObject("Finish").rect)){ levelIndex++; return true; }
			}
			if (Keyboard::isKeyPressed(Keyboard::F3)){
				if (player.getRect().intersects(level.GetObject("Player").rect)){ levelIndex--; return true; }
			}
		}
	}
	void windowFunctions(){
		if (mainWindow(levelIndex)){ windowFunctions(); }
		else return;
	}
	
	~My_Window(){}
};
#endif