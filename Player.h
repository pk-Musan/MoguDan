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

	const int getX() const { return x; }
	const int getY() const { return y; }

	void setPosition( int x, int y );

	void draw();
};