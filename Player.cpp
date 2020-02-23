#include "Player.h"

Player::Player( int x, int y, int maxHp, int maxMp, int attack, int defense, int evasion, int speed ) : 
	Actor( x, y, maxHp, maxMp, attack, defense, evasion, speed ) {
	level = 1;
	exp = 0;
}

Player::~Player() {

}

/*

*/
void Player::draw() {
}