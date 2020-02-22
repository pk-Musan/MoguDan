#include "DungeonLayerManager.h"

DungeonLayerManager::DungeonLayerManager( int width, int height ) : width( width ), height( height ), player( 0 ) {
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
		階段とか罠を設置
	*/

	/*
		アイテムを生成する
	*/

	/*
		playerの位置をランダムに決めてセットしたい
	*/
	if ( player == nullptr ) initPlayerInfo();
	else setPlayerPosition();
}


void DungeonLayerManager::initPlayerInfo() {
	int x, y;
	dungeonLayer->setRandomPointInRoom( x, y );

	player = new Player( x, y, player->INITIAL_MAX_HP, player->INITIAL_MAX_MP, player->INITIAL_STRENGTH, player->INITIAL_DEFENSE );
}

/*
	ダンジョン生成時にプレイヤーの位置をランダムに決定してプレイヤーの座標に格納する
*/
void DungeonLayerManager::setPlayerPosition() {
	int x, y;
	dungeonLayer->setRandomPointInRoom( x, y );
	player->setPosition( x, y );
}


void DungeonLayerManager::setEnemyPosition( /* Enemy& enemy */ ) {
	int x, y;
	do {
		dungeonLayer->setRandomPointInLayer( x, y );
	} while ( abs( player->getX() - x ) <= SPAWN_RANGE && abs( player->getY() - y ) <= SPAWN_RANGE );

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