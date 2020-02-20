#pragma once
#include "DungeonGenerator.h"
#include "Player.h"

/*
	DungeonGeneratorクラスによって自動生成されたフロアとプレイヤー，アイテム，敵などのインスタンスを管理する
*/

class DungeonFloorManager {
private:
	int width, height; // ダンジョンの幅と高さ
	DungeonGenerator* dungeonGenerator; // ダンジョン生成器
	Layer2D* map; // 現在いるフロアの実データ
	std::list<DungeonDivision*>* divisions; // 現在いるフロアの区画情報
	Player player; // プレイヤー
	// itemはmap情報と照らし合わせたいのでmapと同じwidth * height の一次元配列の方がよさそう
	// std::vector<Item*> items;
	// std::vector<Enemy*> enemies;

public:
	DungeonFloorManager( int width, int height );
	~DungeonFloorManager();

	void generateFloor();
	void setPlayerPosition();
};