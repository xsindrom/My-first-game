#ifndef h_Camera
#define h_Camera
#include "Player.h"
View viewMain, viewOff(Vector2f(0, 0), Vector2f(1366, 768));

void cameraLook(Player player){
	if ((player.getX() > 683) && (player.getX() < 3637) && (player.getY() > 384) && (player.getY() < 1376)){ viewMain.setCenter(int(player.getX()), int(player.getY())); }
	if ((player.getX() > 3637) && (player.getY() < 1376 && player.getY() > 384)){ viewMain.setCenter(3637, int(player.getY())); }
	if ((player.getX() < 683) && (player.getY() < 1376 && player.getY() > 384)){ viewMain.setCenter(683, int(player.getY())); }
	if ((player.getY() < 384) && (player.getX() < 3637 && player.getX() > 683)){ viewMain.setCenter(int(player.getX()), 384); }
	if ((player.getY() > 1376) && (player.getX() < 3637 && player.getX() > 683)){ viewMain.setCenter(int(player.getX()), 1376); }
}
void cameraSpecial(){
	if (Keyboard::isKeyPressed(Keyboard::V)){ viewMain.zoom(1.01f); }
	if (Keyboard::isKeyPressed(Keyboard::B)){ viewMain.zoom(0.99f); }
	if (Keyboard::isKeyPressed(Keyboard::Space)){ viewMain.setCenter(400.0, 300.0); }
}
void cameraScroll(double time, Vector2i CursorPosition, int Window_width, int Window_height){
	if (CursorPosition.x < 3){ viewOff.move(-0.5*time, 0); }
	if (CursorPosition.x > Window_width - 3){ viewOff.move(0.5*time, 0); }
	if (CursorPosition.y < 3){ viewOff.move(0, -0.5*time); }
	if (CursorPosition.y > Window_height - 3){ viewOff.move(0, 0.5*time); }
	if (viewOff.getCenter().x < 683) { viewOff.move(0.5*time, 0); }
	if (viewOff.getCenter().x > 3637){ viewOff.move(-0.5*time, 0); }
	if (viewOff.getCenter().y < 384) { viewOff.move(0, 0.5*time); }
	if (viewOff.getCenter().y > 1376){ viewOff.move(0, -0.5*time); }
}
#endif