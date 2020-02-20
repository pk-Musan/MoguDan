#include "Player.h"

Player::Player() : x( -1 ), y( -1 ), level( 1 ) {
	hp = 15;
	mp = 20;
	attack = 5;
	defense = 5;
}

Player::~Player() {

}

void Player::setPosition( int y, int x ) {
	this->y = y;
	this->x = x;
}