#include <iostream>
#include "player_class.h"
using namespace std;

//Function definitions

//Set Player Position
void Player::set_player_pos(double x, double y)
{
	player_x = x;
	player_y = y;

}

//Get Player X
double Player::get_player_x()
{
	return player_x;

}

//Get Player Y
double Player::get_player_y()
{
	return player_y;

}

//Set Player Speed
void Player::set_player_speed(double speed)
{
	player_speed = speed;

}

//Get Player Speed
double Player::get_player_speed()
{
	return player_speed;

}

//Set Direction
void Player::set_player_dir(int direction)
{
	player_dir = direction;

}

//Get Direction
double Player::get_player_dir()
{
	return player_dir;

}



//Step Forward
void Player::step_forward(double framerate)
{


	player_x = cos(framerate);
	player_y = sin(framerate);

}

//Step Backward
void Player::step_backward(double framerate)
{


	player_x = cos(framerate);
	player_y = sin(framerate);

}

//Step Left
void Player::step_left(double framerate)
{


	player_x = cos(framerate);
	player_y = sin(framerate);

}

//Step Right
void Player::step_right(double framerate)
{


	player_x = cos(framerate);
	player_y = sin(framerate);

}

//Turn Left
void Player::turn_left(int amount)
{


	player_dir = amount;

}

//Turn Right
void Player::turn_right(int amount)
{


	player_dir = amount;

}