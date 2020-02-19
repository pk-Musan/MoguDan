#pragma once

#include "DungeonGenerator.h"
#include "Player.h"

/*
	DangeonGeneratorクラスによって自動生成されたフロアとプレイヤー，アイテム，敵などのインスタンスを管理する
*/

class DungeonManager {
private:
	DungeonGenerator dungeonGenerator;
	Player player;
	// std::vector<Item*> items;
	// std::vector<Enemy*> enemies;
};