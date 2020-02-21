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
		�A�C�e���𐶐�����
	*/

	/*
		player�̈ʒu�������_���Ɍ��߂ăZ�b�g������
	*/
	setPlayerPosition();
}


/*
	�_���W�����������Ƀv���C���[�̈ʒu�������_���Ɍ��肵�ăv���C���[�̍��W�Ɋi�[����
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
	�}�b�v�C�A�C�e���C�v���C���[�C�G�̕`��
*/
void DungeonLayerManager::draw() {
	/*
		map�̕`��
	*/

	/*
		�A�C�e���̕`��
	*/

	/*
		�v���C���[�̕`��
	*/

	/*
		�G�̕`��
	*/
}