#include "Player.h"

Player::Player() : x( -1 ), y( -1 ), level( 1 ) {
	hp = 15;
	mp = 20;
	attack = 5;
	defense = 5;
}

Player::~Player() {

}


/*
	プレイヤーの位置をセット
*/
void Player::setPosition( int x, int y ) {
	this->x = x;
	this->y = y;
}


/*

*/
void Player::draw() {}