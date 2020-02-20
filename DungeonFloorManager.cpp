#include "DungeonFloorManager.h"

DungeonFloorManager::DungeonFloorManager( int width, int height ) : width( width ), height( height ), map( 0 ), divisions( 0 ) {
	dungeonGenerator = new DungeonGenerator( width, height );
}

DungeonFloorManager::~DungeonFloorManager() {
	printfDx( "~DngeonFloorManager : start\n" );
	delete dungeonGenerator;
	dungeonGenerator = 0;
	printfDx( "~DngeonFloorManager : end\n" );
}

void DungeonFloorManager::generateFloor() {
	dungeonGenerator->generate();

	map = dungeonGenerator->getLayer();
	divisions = dungeonGenerator->getDivisions();

	/*
		アイテムを生成する
	*/

	/*
		playerの位置をランダムに決めてセットしたい
	*/
	setPlayerPosition();

	map->Dump();
}

void DungeonFloorManager::setPlayerPosition() {
	int roomNumber = rand() % divisions->size();

	std::list<DungeonDivision*>::iterator itr;
	for ( DungeonDivision* div : *divisions ) {
		if ( roomNumber == 0 ) {
			int x = rand() % ( div->inner.getWidth() ) + div->inner.left;
			int y = rand() % ( div->inner.getHeight() ) + div->inner.top;
			player.setPosition( y, x );
			break;
		} else roomNumber--;
	}
}