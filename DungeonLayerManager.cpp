#include "DungeonLayerManager.h"

DungeonLayerManager::DungeonLayerManager( int width, int height ) : width( width ), height( height ) {
	dungeonLayer = new DungeonLayer( width, height );
}

DungeonLayerManager::~DungeonLayerManager() {
	printfDx( "~DngeonFloorManager : start\n" );
	delete dungeonLayer;
	dungeonLayer = 0;
	printfDx( "~DngeonFloorManager : end\n" );
}

void DungeonLayerManager::generateLayer() {
	dungeonLayer->generate();

	/*
		アイテムを生成する
	*/

	/*
		playerの位置をランダムに決めてセットしたい
	*/
	setPlayerPosition();
}


/*
	ダンジョン生成時にプレイヤーの位置をランダムに決定してプレイヤーの座標に格納する
*/
void DungeonLayerManager::setPlayerPosition() {
	int x, y;
	dungeonLayer->setRandomPointInRoom( x, y );
	player.setPosition( x, y );
}


void DungeonLayerManager::setEnemyPosition( /* Enemy& enemy */ ) {
	int x, y;
	do {
		dungeonLayer->setRandomPointInLayer( x, y );
	} while ( abs( player.getX() - x ) <= SPAWN_RANGE && abs( player.getY() - y ) <= SPAWN_RANGE );

	// enemy.setPosition( x, y );
}


/*
	マップ，アイテム，プレイヤー，敵の描画
*/
void DungeonLayerManager::draw() {
	/*
		mapの描画
	*/

	/*
		アイテムの描画
	*/

	/*
		プレイヤーの描画
	*/

	/*
		敵の描画
	*/
}