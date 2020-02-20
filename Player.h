#pragma once
#include <vector>

class Player {
private:
	int x, y;
	int attack, defense;
	int hp, mp;
	int level;
	//std::vector<Item*> items;

public:
	Player();
	~Player();
	void setPosition( int y, int x );
};