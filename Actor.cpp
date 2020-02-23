#include "Actor.h"

Actor::Actor( int x, int y, int maxHp, int maxMp, int attack, int defense, int evasion, int speed ) :
	x( x ), y( y ), maxHp( maxHp ), maxMp( maxMp ), hp( maxHp ), mp( maxMp ),
	attack( attack ), defense( defense ), evasion( evasion ), speed( speed ), animationCount( 0 ),
	state( KEY_INPUT ), direction( DOWN ), animeState( DEFAULT ) {}

Actor::~Actor() {

}

void Actor::setPosition( int x, int y ) {
	this->x = x;
	this->y = y;
}

void Actor::draw() {

}