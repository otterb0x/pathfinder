#include <iostream>
using namespace std;

class Player
{
private:
	//Variables to hold the player's position and speed.
	float player_x, player_y, player_speed;

public:
	//Function to set the player's position.
	void set_player_pos(float x, float y);

	//Function to get the player's X position.
	float get_player_x();

	//Function to get the player's Y position.
	float get_player_y();

	//Function to set the player's speed.
	void set_player_speed(float speed);

	//Function to get the player's speed.
	float get_player_speed();


};

//Function definitions

//Set Player Position
void Player::set_player_pos(float x, float y)
{
	player_x = x;
	player_y = y;

}

//Get Player X
float Player::get_player_x()
{
	return player_x;

}

//Get Player X
float Player::get_player_y()
{
	return player_y;

}

//Set Player Speed
void Player::set_player_speed(float speed)
{
	player_speed = speed;

}

//Get Player Speed
float Player::get_player_speed()
{
	return player_speed;

}
