#include "Player.h"
#define PI 3.1415926535897932384626433832795028841971693993751
Player::Player():Parent(){
	CurrentFrame = 0.0;
	x = 0.0;
	y = 0.0;
	dx = 0.0;
	dy = 0.0;
	speed = 0;
	width = 0.0;
	height = 0.0;
	heroScore = 0;
	heroHealth = 0;
	heroLifes = 0;
	heroBullets = 0;
	isShoot = false;
	sprite.setOrigin(width / 2, height / 2);
	name_file = "elven_archer.png";
	Name = "";
	if (!texture.loadFromFile("images\\hero\\" + name_file)){ return; }
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(12, 10, width, height));
	sprite.setPosition(x, y);
}
Player::Player(const double x_, const double y_, const double w_, const double h_ ,const string name,Level &level, const string Name_):Parent(x_,y_,w_,h_,Name_,name){
	CurrentFrame = 0.0;
	x = x_;
	y = y_;
	width = w_;
	height = h_;
	dx = 0;
	dy = 0;
	speed = 0;
	name_file = Name_;
	Name = name;
	heroScore = 0;
	heroHealth = 100;
	heroLifes = 3;
	heroBullets = 10;
	isShoot = false;
	if (!texture.loadFromFile("images\\hero\\" + name_file)){ return; }
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(12, 10, w_, h_));
	sprite.setPosition(x_, y_);
	obj = level.GetAllObjects();
}

Player::Player(const Player &player){
	CurrentFrame = player.CurrentFrame;
	x = player.x;
	y = player.y;
	dx = player.x;
	dy = player.y;
	speed = player.speed;
	width = player.width;
	height = player.height;
	dir = player.dir;
	heroHealth = player.heroHealth;
	heroLifes = player.heroLifes;
	heroBullets = player.heroBullets;
	name_file = player.name_file;
	Name = player.Name;
	if (!texture.loadFromFile("images\\hero\\"+name_file)){ return; }
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(12.0, 10.0, width, height));
	sprite.setPosition(x, y);
	obj = player.obj;
}

void Player::interactionMap(){
	for (unsigned int i = 0; i < obj.size(); i++){
		if (getRect().intersects(obj[i].rect)){
			if ((obj[i].name == "Wall") || (obj[i].name == "Jungle") || (obj[i].type == "Solid")||(obj[i].name == "Block")){
				if (dy > 0){ y = obj[i].rect.top - height; }
				if (dx > 0){ x = obj[i].rect.left - width; }
				if (dy < 0){ y = obj[i].rect.top + obj[i].rect.height; }
				if (dx < 0){ x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
	}
	if (x < 0){ x = 0; }
	if (x > 4319){ x = 4319; }
	if (y < 0){ y = 0; }
	if (y > 1759){ y = 1759; }
}

void Player::resetHeroScore(){
	if (Keyboard::isKeyPressed(Keyboard::T)){ heroScore = 0; }
	if (Keyboard::isKeyPressed(Keyboard::Escape)){
		if (dx > 0){ x += 20; }
		if (dy > 0){ y += 20; }
		if (dx < 0){ x -= 20; }
		if (dy < 0){ y -= 20; }
	}
}
void Player::move(double time){
	if ((x >= 0) && (x < 4320) && (y >= 0) && (y < 1760)){
		if (heroLifes > 0){
			CurrentFrame += 0.0025f*time;
			if (CurrentFrame > 5){ CurrentFrame -= 5; }
			if (Keyboard::isKeyPressed(Keyboard::Right)){
				dir = 0; speed = 0.1f;
				sprite.setTextureRect(IntRect(156, int(CurrentFrame) * 72, width, height));
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)){
				dir = 1; speed = 0.1f;
				sprite.setTextureRect(IntRect(216, int(CurrentFrame) * 72, -width, height));
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)){
				dir = 2; speed = 0.1f;
				sprite.setTextureRect(IntRect(298, int(CurrentFrame) * 72, width, height));
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)){
				dir = 3; speed = 0.1f;
				sprite.setTextureRect(IntRect(12, int(CurrentFrame) * 72, width, height));
			}
		}
		if (heroLifes < 0){
			heroHealth = 0; heroLifes = 0;
			sprite.setTextureRect(IntRect(154, 658, width + 10, height));
		}
	}
}
void Player::DirectionDependence(int number,double time){
	switch (number){
	case 1:
		switch (dir){
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}
		break;
	case 2:
		speed = 0.1;
		switch (dir){
		case 0: dx = -speed; dy = 0; break;
		case 1: dx = speed; dy = 0; break;
		case 2: dx = 0; dy = -speed; break;
		case 3: dx = 0; dy = speed; break;
		}
		break;
	}
	x += dx*time;
	y += dy*time;
	speed = 0;
	sprite.setPosition(x, y);
}
void Player::update(double time, Sound &sound){
	move(time);
	if (heroLifes > 0){
		DirectionDependence(1, time);
		interactionMap();
		resetHeroScore();
	}
}
ostringstream Player::heroHealthString(){
	ostringstream heroHealth_String;
	heroHealth_String << heroHealth;
	return heroHealth_String;
}
ostringstream Player::heroLifesString(){
	ostringstream heroLifes_String;
	heroLifes_String << heroLifes;
	return heroLifes_String;
}
ostringstream Player::heroBulletsString(){
	ostringstream heroBullets_String;
	heroBullets_String << heroBullets;
	return heroBullets_String;
}
ostringstream Player::heroScoreString(){
	ostringstream heroScore_String;
	heroScore_String << heroScore;
	return heroScore_String;
}
ostringstream Player::gameString(int GameTime){
	ostringstream gameTimeString;
	gameTimeString << GameTime;
	return gameTimeString;
}
Text Player::HeroScore(Text &text){
	ostringstream heroScoreString;
	heroScoreString << heroScore;
	text.setString("Score: " + heroScoreString.str() + "\nLifes: " + heroLifesString().str()
		+ "\nHealth: " + heroHealthString().str());
	text.setPosition(x + width, y - height);
	return text;
}
void Player::showEnd(RenderWindow &window, Text &text, View &view,Texture end_texture){
	Sprite end_sprite(end_texture);
	end_sprite.setPosition(x + width, y - height);
	end_sprite.scale(0.4f*view.getSize().x / window.getSize().x, 0.4f*view.getSize().y / window.getSize().y);
	for (unsigned int i = 0; i < obj.size(); i++){
		if (getRect().intersects(obj[i].rect)){
			if (obj[i].name == "Finish"){
				HeroScore(text);
				window.draw(end_sprite);
				window.draw(text);
			}
		}
	}
}

void Player::showStats(RenderWindow &window, Text &text, View &view,int GameTime)
{
	text.setStyle(Style::Close);
	text.setString(getName()+"\nHealth: " + heroHealthString().str() + "\nLifes: " + heroLifesString().str()
		+ "\nBullets: " + heroBulletsString().str() + "\nTime: " + gameString(GameTime).str());
	text.setScale(view.getSize().x / window.getSize().x, view.getSize().y / window.getSize().y);
	text.setPosition(x, y-120);
	window.draw(text);
}

void Player::gameOver(RenderWindow &window, Text &text, View &view, int GameTime){
	if (heroLifes < 1){
		text.setString("Game Over\nTime: " + gameString(GameTime).str());
		text.setPosition(x, y - 160);
		text.setScale(view.getSize().x / window.getSize().x, view.getSize().y / window.getSize().y);
		window.draw(text);
	}
}
void Player::attack(double time, Sound &sound, Event event){
	if (event.type == Event::KeyReleased){
		if (event.key.code == Keyboard::A){
			if (name_file == "elven_archer.png", "mage.png"){
				if (heroBullets > 0){
					if (CurrentFrame > 2){ CurrentFrame -= 2; }
					switch (dir){
					case 0:sprite.setTextureRect(IntRect(156, int(CurrentFrame) * 72 + 296, width, height)); break;
					case 1:sprite.setTextureRect(IntRect(216, int(CurrentFrame) * 72 + 296, -width, height)); break;
					case 2:sprite.setTextureRect(IntRect(298, int(CurrentFrame) * 72 + 296, width, height));  break;
					case 3:sprite.setTextureRect(IntRect(12, int(CurrentFrame) * 72 + 296, width, height));  break;
					}
					isShoot = true;
					heroBullets--;
					sound.play();
				}
			}
		}
	}
}
void Player::teleport(Level &level,int levelIndex){
	if (levelIndex == 2){
		if (getRect().intersects(level.GetObject("TpA").rect)){
			x = level.GetObject("TpB").rect.left;
			y = level.GetObject("TpB").rect.top;
		}
	}
	else return;
}
double FindAngel(double x0, double y0, double x1, double y1){
	double koef = 0.0;
	koef = sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
	double x_vector = 0.0, y_vector = 0.0;
	x_vector = (x1 - x0) / koef; y_vector = (y1 - y0) / koef;
	double angl = 0.0;
	angl = acos(x_vector * 1 + y_vector * 0) * 180 / PI;
	return angl;
}
void Player::Intersection(Vertex *line, double x0, double y0, double x1, double y1, double time){//
	if (((x0 >= line[0].position.x) && (x0 <= line[1].position.x))
		|| ((x0  >= line[1].position.x) && (x0  <= line[0].position.x))){
		if (((line[0].position.y <= y0) && (y0  <= line[1].position.y))
			|| ((line[1].position.y <= y0 )) && ((y0 <= line[0].position.y))){
			double FirstZ = (line[0].position.x - line[1].position.x)*(y0 - line[1].position.y) - (line[0].position.y - line[1].position.y)*(x0 - line[1].position.x);
			double SecondZ = (line[0].position.x - line[1].position.x)* (y1 - line[0].position.y) - (line[0].position.y - line[1].position.y)*(x1 - line[0].position.x);
			double ThirdZ = (line[1].position.x - line[0].position.x)*(y0 - line[0].position.y) - (line[1].position.y - line[0].position.y)*(x0 - line[0].position.x);
			double Foutrh = (line[1].position.x - line[0].position.x)*(y1 - line[1].position.y) - (line[1].position.y - line[0].position.y)*(x0 - line[1].position.x);
			bool intersection = false;
			if (((FirstZ >= 0 && Foutrh >= 0) && (SecondZ <= 0 && ThirdZ <= 0))
				|| ((FirstZ <= 0 && Foutrh <= 0) && (SecondZ >= 0 && ThirdZ >= 0))){
				intersection = true;
				DirectionDependence(2, time);
			}
			else { intersection = false; };
		}
	}
}
	
void Player::interactionBarier(Vertex *line, double time){
	if (90 >= FindAngel(line[0].position.x, line[0].position.y, line[1].position.x, line[1].position.y) >= 0){
		Intersection(line, x, y, x + width, y + height, time);
	}
	if (90 <= FindAngel(line[0].position.x, line[0].position.y, line[1].position.x, line[1].position.y) <= 180){
		Intersection(line, x, y + height, x + width, y, time);
	}
}