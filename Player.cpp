#include "Player.h"

Player::Player( int x, int y, int maxHp, int maxMp, int strength, int defense ) : Actor( x, y, maxHp, maxMp, strength, defense ) {
	level = 1;
	exp = 0;
}

Player::~Player() {

}

/*

*/
void Player::draw() {}