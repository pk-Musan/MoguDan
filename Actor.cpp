#include "Actor.h"

Actor::Actor( int x, int y, int maxHp, int maxMp, int strength, int defense ) :
	x( x ), y( y ), maxHp( maxHp ), maxMp( maxMp ), hp( maxHp ), mp( maxMp ), strength( strength ), defense( defense ) {}

Actor::~Actor() {

}

void Actor::setPosition( int x, int y ) {
	this->x = x;
	this->y = y;
}

