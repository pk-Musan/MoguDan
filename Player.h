#pragma once
#include "Actor.h"
#include <vector>

class Player : public Actor {
public:
	const static int INITIAL_MAX_HP = 15;
	const static int INITIAL_MAX_MP = 20;
	const static int INITIAL_ATTACK = 5;
	const static int INITIAL_DEFENSE = 5;
	const static int INITIAL_EVASION = 2;
	const static int INITIAL_SPEED = 1;

private:
	int level;
	int exp;
	//std::vector<Item*> items;

public:
	Player( int x, int y, int maxHp, int maxMp, int attack, int defense, int evasion, int speed );
	~Player();

	void draw();
};