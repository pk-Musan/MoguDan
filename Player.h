#pragma once
#include "Actor.h"
#include <vector>

class Player : public Actor {
public:
	const static int INITIAL_MAX_HP = 15;
	const static int INITIAL_MAX_MP = 20;
	const static int INITIAL_STRENGTH = 5;
	const static int INITIAL_DEFENSE = 5;

private:
	int level;
	int exp;
	//std::vector<Item*> items;

public:
	Player( int x, int y, int maxHp, int maxMp, int strength, int defense );
	~Player();

	void draw();
};