#pragma once
#include "DungeonLayer.h"
#include "Player.h"

/*
	DungeonGeneratorクラスによって自動生成されたフロアとプレイヤー，アイテム，敵などのインスタンスを管理する
*/
class DungeonLayerManager {

public:
	const static int SPAWN_RANGE = 8;

private:
	int width, height; // ダンジョンの幅と高さ
	DungeonLayer* dungeonLayer; // ダンジョン生成器
	Player* player; // プレイヤー
	// itemはmap情報と照らし合わせたいのでmapと同じwidth * height の一次元配列の方がよさそう
	// std::vector<Item*> items;
	// std::vector<Enemy*> enemies;

public:
	DungeonLayerManager( int width, int height );
	~DungeonLayerManager();

	void generateLayer();
	void initPlayerInfo();
	void setPlayerPosition();
	void setEnemyPosition( /* Enemy& enemy */ );

	//void ();

	void draw();
};