#include "Enemy.h"
Enemy::Enemy():Parent(){
	CurrentFrame = 0.0;
	CurrentFrameOff = 0.0;
	x = 0.0;
	y = 0.0;
	width = 0.0;
	height = 0.0;
	speed = 0.0;
	dx = 0.0;
	dy = 0.0;
	isLife = true;
	isMove = true;
	isAttacked = false;
	enemyHealth = 0;
	name_file = "images\\orc\\ogre.png";
	Name = "";
	if (!texture.loadFromFile(name_file)){ return; }
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(12.0, 10.0, width, height));
	sprite.setPosition(x, y);
	sprite.setOrigin(width / 2, height / 2);
	vertical_start_fence = 0;
	horizontal_start_fence = 0;
	vertical_end_fence = 0;
	horizontal_end_fence = 0;
}

Enemy::Enemy(const double x_, const double y_, const double width_, const double height_,const string Name, Level &level, const string NM) :Parent(x_,y_,width_,height_,NM,Name){
	isLife = true;
	isMove = true;
	isAttacked = false;
	obj = level.GetAllObjects();
	CurrentFrame = 0.0;
	CurrentFrameOff = 0.0;
	x = x_;
	y = y_;
	width = width_;
	height = height_;
	name_file = NM;
	CurrentFrame = 0.0;
	dx = 0.0;
	dy = 0.0;
	vertical_start_fence = 0;
	horizontal_start_fence = 0;
	vertical_end_fence = 0;
	horizontal_end_fence = 0;
	enemyHealth = 100;
	if (!texture.loadFromFile(name_file)){ return; }
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(12, 10, width, height));
	sprite.setPosition(x_, y_);
}

Enemy::Enemy(const double x_, const double y_, const  double width_, const double height_,
	const double vsf,const double vef,const double hsf,const double hef,const string name,Level &level, const string NM){
	isLife = true;
	isMove = true;
	isAttacked = false;
	obj = level.GetAllObjects();
	CurrentFrame = 0.0;
	CurrentFrameOff = 0.0;
	x = x_;
	y = y_;
	width = width_;
	height = height_;
	name_file = NM;
	Name = name;
	dx = 0.0;
	dy = 0.0;
	CurrentFrame = 0.0;
	vertical_start_fence = vsf;
	horizontal_start_fence = hsf;
	vertical_end_fence = vef;
	horizontal_end_fence = hef;
	enemyHealth = 100;
	if (!texture.loadFromFile(name_file)){ return; }
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(12, 10, width, height));
	sprite.setPosition(x_, y_);
}

Enemy::Enemy(const Enemy &enemy){
	CurrentFrame = enemy.CurrentFrame;
	CurrentFrameOff = enemy.CurrentFrameOff;
	x = enemy.x;
	y = enemy.y;
	width = enemy.width;
	height = enemy.height;
	speed = enemy.speed;
	dx = enemy.dx;
	dy = enemy.dy;
	name_file = enemy.name_file;
	vertical_start_fence = enemy.vertical_start_fence;
	horizontal_start_fence = enemy.horizontal_start_fence;
	vertical_end_fence = enemy.vertical_end_fence;
	horizontal_end_fence = enemy.horizontal_end_fence;
	enemyHealth = enemy.enemyHealth;
	if (!texture.loadFromFile(enemy.name_file)){ return; }
	sprite.setTexture(enemy.texture);
	sprite.setTextureRect(IntRect(12, 10, enemy.width, enemy.height));
	sprite.setPosition(enemy.x, enemy.y);
	sprite.setOrigin(enemy.width / 2, enemy.height / 2);
}

ostringstream Enemy::getEnemyHealthString(){
	ostringstream enemyHealth_string;
	enemyHealth_string << enemyHealth;
	return enemyHealth_string;
}

void Enemy::move(double time){
	if ((enemyHealth > 0) && (isMove)){
		CurrentFrame += 0.004*time;
		if (CurrentFrame > 5) { CurrentFrame -= 5; }
		switch (dir){
		case 0:speed = 0.08; sprite.setTextureRect(IntRect(216, int(CurrentFrame) * 72 + 10, -width, height));  break;
		case 1:speed = 0.08; sprite.setTextureRect(IntRect(156, int(CurrentFrame) * 72 + 10, width, height)); break;
		case 2:speed = 0.08; sprite.setTextureRect(IntRect(12, int(CurrentFrame) * 72 + 10, width, height)); break;
		case 3:speed = 0.08; sprite.setTextureRect(IntRect(298, int(CurrentFrame) * 72 + 10, width, height)); break;
		case 4:speed = 0.04; sprite.setTextureRect(IntRect(80, int(CurrentFrame) * 72 + 10, width, height));  break;
		case 5:speed = 0.04; sprite.setTextureRect(IntRect(140, int(CurrentFrame) * 72 + 10, -width, height)); break;
		case 6:speed = 0.04; sprite.setTextureRect(IntRect(288, int(CurrentFrame) * 72 + 10, -width, height)); break;
		case 7:speed = 0.04; sprite.setTextureRect(IntRect(228, int(CurrentFrame) * 72 + 10, width, height)); break;
		}
	}
	if (enemyHealth <= 0){
		CurrentFrameOff += 0.0008*time;
		sprite.setTextureRect(IntRect(154, int(CurrentFrameOff) * 72 + 658, width + 10, height));
		if (CurrentFrameOff > 4.5){ isLife = false; }
	}
}
void Enemy::showStats(RenderWindow &window, Text &text){
	text.setString(getName()+"\nHealth: " + getEnemyHealthString().str());
	text.setPosition(x, y - sprite.getScale().y*height);
	window.draw(text);
}
void Enemy::interactionPlayer(Player &player, double time, Sound &sound_attack){
	if (enemyHealth > 0){
		if (CurrentFrame > 4) { CurrentFrame -= 4; }
		if (player.getHeroHealth() < 1){ player.setHeroLifes(player.getHeroLifes() - 1); player.setHeroHealth(100); }
		if (getRect().intersects(player.getRect())){
			switch (dir){
			case 0:
				sprite.setTextureRect(IntRect(156, int(CurrentFrame) * 72 + 368, width + 7, height + 10));
				if (int(CurrentFrame) == 3){ player.setHeroHealth(player.getHeroHealth() - 5); sound_attack.play(); }
				break;
			case 1:
				sprite.setTextureRect(IntRect(216, int(CurrentFrame) * 72 + 368, -width - 7, height + 10));
				if (int(CurrentFrame) == 3){ player.setHeroHealth(player.getHeroHealth() - 5); sound_attack.play(); }
				break;
			case 2:
				sprite.setTextureRect(IntRect(12, int(CurrentFrame) * 72 + 368, width + 2, height + 2));
				if (int(CurrentFrame) == 3){ player.setHeroHealth(player.getHeroHealth() - 5); sound_attack.play(); }
				break;
			case 3:
				sprite.setTextureRect(IntRect(298, int(CurrentFrame) * 72 + 368, width + 2, height + 2));
				if (int(CurrentFrame) == 3){ player.setHeroHealth(player.getHeroHealth() - 5); sound_attack.play(); }
				break;
			case 4:
				sprite.setTextureRect(IntRect(80, int(CurrentFrame) * 72 + 368, width + 2, height + 2));
				if (int(CurrentFrame) == 3){ player.setHeroHealth(player.getHeroHealth() - 5); sound_attack.play(); }
				break;
			case 5:
				sprite.setTextureRect(IntRect(140, int(CurrentFrame) * 72 + 368, -width - 2, height + 2));
				if (int(CurrentFrame) == 3){ player.setHeroHealth(player.getHeroHealth() - 5); sound_attack.play(); }
				break;
			case 6:
				sprite.setTextureRect(IntRect(288, int(CurrentFrame) * 72 + 368, -width - 2, height + 2));
				if (int(CurrentFrame) == 3){ player.setHeroHealth(player.getHeroHealth() - 5); sound_attack.play(); }
				break;
			case 7:
				sprite.setTextureRect(IntRect(228, int(CurrentFrame) * 72 + 368, width + 2, height + 2));
				if (int(CurrentFrame) == 3){ player.setHeroHealth(player.getHeroHealth() - 5); sound_attack.play(); }
				break;
			default:sprite.setTextureRect(IntRect(298, int(CurrentFrame) * 72 + 368, width + 2, height + 2));
				break;
			}
		}
	}
}
void Enemy::update(double time, double Vertical_start_fence, double Vertical_end_fence,
	double Horizontal_start_fence, double Horizontal_end_fence, Player &player, Sound &sound_attack){
	move(time);
	if (Vertical_start_fence < Vertical_end_fence){
		if ((y <= Vertical_start_fence)){ dy = speed; dir = 3; dx = 0.0; }
		if (y >= Vertical_end_fence){ dy = -speed; dir = 2; dx = 0.0; }
	}
	if (Vertical_start_fence > Vertical_end_fence){
		if ((y > Vertical_start_fence)){ dy = -speed; dir = 2; dx = 0.0; }
		if (y < Vertical_end_fence){ dy = speed; dir = 3; dx = 0.0; }
	}

	if (Horizontal_start_fence < Horizontal_end_fence){
		if (x <= Horizontal_start_fence){ dx = speed; dir = 1; dy = 0.0; }
		if (x >= Horizontal_end_fence){ dx = -speed; dir = 0; dy = 0.0; }
	}
	if (Horizontal_start_fence > Horizontal_end_fence){
		if (x >= Horizontal_start_fence){ dx = -speed; dir = 0; dy = 0.0; }
		if (x <= Horizontal_end_fence){dx = speed; dir = 1; dy = 0.0;}
	}
	x += dx * time;
	y += dy * time;
	speed = 0;
	sprite.setPosition(x, y);
	interactionPlayer(player, time, sound_attack);
}
void Enemy::update(double time, Player &player, Sound &sound_attack){
	move(time);
	if ((enemyHealth > 0) && (isMove)){
		if ((vertical_start_fence < vertical_end_fence) && (horizontal_start_fence == horizontal_end_fence)){
			if ((y <= vertical_start_fence)){ dy = speed; dir = 3; dx = 0.0; }
			if (y >= vertical_end_fence){ dy = -speed; dir = 2; dx = dx = 0.0; }
		}
		if ((vertical_start_fence > vertical_end_fence) && (horizontal_start_fence == horizontal_end_fence)){
			if ((y > vertical_start_fence)){ dy = -speed; dir = 2; dx = 0.0; }
			if (y < vertical_end_fence){ dy = speed; dir = 3; dx = 0.0; }
		}

		if ((horizontal_start_fence < horizontal_end_fence)&&(vertical_start_fence == vertical_end_fence)){
			if (x <= horizontal_start_fence){ dx = speed; dir = 1; dy = 0.0; }
			if (x >= horizontal_end_fence){ dx = -speed; dir = 0; dy = 0.0; }
		}
		if ((horizontal_start_fence > horizontal_end_fence) && (vertical_start_fence == vertical_end_fence)){
			if (x >= horizontal_start_fence){ dx = -speed; dir = 0; dy = 0.0; }
			if (x <= horizontal_end_fence){ dx = speed; dir = 1; dy = 0.0; }
		}
		x += dx * time;
		y += dy * time;
		
	}
	double tan = abs((player.getY() - y) / (player.getX() - x));
	if (abs(atan(tan)) < 2){
		interactionMap(time, tan);
	}
	speed = 0;
	sprite.setPosition(x, y);
	
}

void Enemy::kill(Bullet *bullet, double time){
	if (getRect().intersects(bullet->getRect())){
		sprite.setColor(Color::Red);
		isAttacked = true;
		enemyHealth -= 15;
		bullet->setLife(false);
		if (enemyHealth <= 0){
			enemyHealth = 0;
		}
	}
	else { sprite.setColor(Color::White); }
}

bool Enemy::interactionMap(double time, double tan){
	for (unsigned int i = 0; i < obj.size(); i++){
		if (getRect().intersects(obj[i].rect)){
			if ((obj[i].name == "Wall") || (obj[i].name == "Jungle") || (obj[i].type == "Solid")){
				switch (dir){
				case 0:speed = 0.08; dx = -speed; dy = 0; break;
				case 1:speed = 0.08; dx = speed; dy = 0; break;
				case 2:speed = 0.08; dx = 0; dy = speed; break;
				case 3:speed = 0.08; dx = 0; dy = -speed; break;
				case 4:speed = 0.04; dx = -speed; dy = tan*speed; break;
				case 5:speed = 0.04; dx = speed; dy = tan*speed; break;
				case 6:speed = 0.04; dx = speed; dy = -tan*speed; break;
				case 7:speed = 0.04; dx = -speed; dy = -tan*speed; break;
				}
				x += dx*time;
				y += dy*time;
				speed = 0;
				isMove = false; isAttacked = false;
				return true;
			}
		}
	}
	return false;
}
void Enemy::playerDetection(Player &player, double time, Sound &sound){
	if (FloatRect(x - sprite.getScale().x*200, y - sprite.getScale().y*200,
		sprite.getScale().x * 400, sprite.getScale().y * 400).intersects(player.getRect())){
		if ((enemyHealth > 0)){
			isMove = false;
			CurrentFrame += 0.004*time;
			if (CurrentFrame > 5) { CurrentFrame -= 5; }
			double tan = 0.0;//
			if (abs(atan(abs((player.getY() - y) / (player.getX() - x)))) < 2){ tan = abs((player.getY() - y) / (player.getX() - x)); }//
			if (!interactionMap(time, tan)){//
				if (abs(y - player.getY()) < 30 * sprite.getScale().y){
					if (x < player.getX()){ speed = 0.08;  dir = 0; dx = speed; dy = 0; sprite.setTextureRect(IntRect(156, int(CurrentFrame) * 72 + 10, width, height)); }
					if (x > player.getX()){ speed = 0.08; dir = 1; dx = -speed; dy = 0; sprite.setTextureRect(IntRect(216, int(CurrentFrame) * 72 + 10, -width, height)); }
				}
				else if (abs(x - player.getX()) < 30 * sprite.getScale().x){
					if (y > player.getY()){ speed = 0.08; dir = 2; dy = -speed; dx = 0; sprite.setTextureRect(IntRect(12, int(CurrentFrame) * 72 + 10, width + 2, height + 2)); }
					if (y < player.getY()){ speed = 0.08; dir = 3; dy = speed; dx = 0; sprite.setTextureRect(IntRect(298, int(CurrentFrame) * 72 + 10, width + 2, height + 2)); }
				}
				else if ((abs(y - player.getY()) > 30 * sprite.getScale().y) && (abs(x - player.getX()) > 30 * sprite.getScale().x)){
					if ((player.getY() < y) && (player.getX() > x)){ speed = 0.04; dx = speed; dy = -speed*tan; dir = 4; sprite.setTextureRect(IntRect(80, int(CurrentFrame) * 72 + 10, width, height)); }
					if ((player.getY() < y) && (player.getX() < x)){ speed = 0.04; dx = -speed; dy = -speed*tan; dir = 5; sprite.setTextureRect(IntRect(140, int(CurrentFrame) * 72 + 10, -width, height)); }
					if ((player.getY() > y) && (player.getX() < x)){ speed = 0.04; dx = -speed; dy = speed*tan; dir = 6; sprite.setTextureRect(IntRect(288, int(CurrentFrame) * 72 + 10, -width, height)); }
					if ((player.getY() > y) && (player.getX() > x)){ speed = 0.04; dx = speed; dy = speed*tan; dir = 7; sprite.setTextureRect(IntRect(228, int(CurrentFrame) * 72 + 10, width, height)); }
				}
			}
			interactionPlayer(player, time, sound);
			if (sqrt(pow(player.getX() - x, 2) + pow(player.getY() - y, 2)) > width*sprite.getScale().x){ x += dx*time; y += dy*time; }

			speed = 0;
			sprite.setPosition(x, y);
		}
	}
	else{ stay(time); }
}
void Enemy::stay(double time){
	if ((!isMove) && (enemyHealth > 0)){
		CurrentFrame += 0.0004*time;
		if (CurrentFrame > 6) { CurrentFrame -= 6; }
		sprite.setTextureRect(IntRect(12 + int(CurrentFrame) * 72, 10, width, height));
	}
}
void enemiesPlayerDetection(list<Enemy*>::iterator it, list<Enemy*>enemies, Player &player, double time, Sound &sound){
	for (it = enemies.begin(); it != enemies.end(); it++){
		(*it)->playerDetection(player, time, sound);
	}
}
void enemiesShowStats(list<Enemy*>::iterator it, list<Enemy*>enemies,RenderWindow &window,Text &text){
	for (it = enemies.begin(); it != enemies.end(); it++){
		(*it)->showStats(window, text);
	}
}
void enemiesInitialize(list<Enemy*>&enemies, Level &level, string ObjectName){
	vector<Object> e = level.GetObjects(ObjectName);
	if (ObjectName == "Enemy_horizontalOgre"){
		for (unsigned int i = 0; i < e.size(); i++){
			enemies.push_back(new Enemy(e[i].rect.left, e[i].rect.top, 55.0, 50.0, 0, 0, e[i].rect.left + 1, e[i].rect.left + 100, "Ogre", level, "images\\orc\\ogre.png"));
		}
	}
	if (ObjectName == "Enemy_verticalOgre"){
		for (unsigned int i = 0; i < e.size(); i++){
			enemies.push_back(new Enemy(e[i].rect.left, e[i].rect.top, 55.0, 50.0, e[i].rect.top + 1, e[i].rect.top + 100, 0, 0,"Ogre", level, "images\\orc\\ogre.png"));
		}
	}
	if (ObjectName == "Enemy_horizontalGrunt"){
		for (unsigned int i = 0; i < e.size(); i++){
			enemies.push_back(new Enemy(e[i].rect.left, e[i].rect.top, 55.0, 50.0, 0, 0, e[i].rect.left + 1, e[i].rect.left + 100,"Grunt", level, "images\\orc\\grunt.png"));
		}
	}
	if (ObjectName == "Enemy_verticalGrunt"){
		for (unsigned int i = 0; i < e.size(); i++){
			enemies.push_back(new Enemy(e[i].rect.left, e[i].rect.top, 55.0, 50.0, e[i].rect.top + 1, e[i].rect.top + 100, 0, 0, "Grunt", level, "images\\orc\\grunt.png"));
		}
	}
	if (ObjectName == "Enemy_horizontalPeon"){
		for (unsigned int i = 0; i < e.size(); i++){
			enemies.push_back(new Enemy(e[i].rect.left, e[i].rect.top, 55.0, 50.0, 0, 0, e[i].rect.left + 1, e[i].rect.left + 100,"Peon", level, "images\\orc\\peon.png"));
		}
	}
	if (ObjectName == "Enemy_verticalPeon"){
		for (unsigned int i = 0; i < e.size(); i++){
			enemies.push_back(new Enemy(e[i].rect.left, e[i].rect.top, 55.0, 50.0, e[i].rect.top + 1, e[i].rect.top + 100, 0, 0, "Peon", level, "images\\orc\\peon.png"));
		}
	}
}
void enemiesUpdate(list<Enemy*>::iterator it, list<Enemy*>enemies, Player &player, Sound &sound_attack, double time){
	for (it = enemies.begin(); it != enemies.end(); it++){ (*it)->update(time, player, sound_attack); }
}
void enemiesDraw(list<Enemy*>::iterator it, list<Enemy*>enemies, RenderWindow &window){
	for (it = enemies.begin(); it != enemies.end(); it++){ window.draw((*it)->getSprite()); }
}
void enemiesInteractionBullets(list<Enemy*>::iterator it, list <Enemy*>&enemies, list<Bullet*>::iterator bt, list<Bullet*> &bullets,double time,Player &player){
	for (it = enemies.begin(); it != enemies.end();){
		for (bt = bullets.begin(); bt != bullets.end(); bt++){
			(*it)->kill((*bt),time);
		}
		if ((*it)->getIsLife() == false){
			player.setHeroBullets(player.getHeroBullets() + 7);
			it = enemies.erase(it);
		}
		else it++;
	}
}