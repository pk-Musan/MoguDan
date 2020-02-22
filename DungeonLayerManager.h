#pragma once
#include "DungeonLayer.h"
#include "Player.h"

/*
	DungeonGenerator�N���X�ɂ���Ď����������ꂽ�t���A�ƃv���C���[�C�A�C�e���C�G�Ȃǂ̃C���X�^���X���Ǘ�����
*/
class DungeonLayerManager {

public:
	const static int SPAWN_RANGE = 8;

private:
	int width, height; // �_���W�����̕��ƍ���
	DungeonLayer* dungeonLayer; // �_���W����������
	Player* player; // �v���C���[
	// item��map���ƏƂ炵���킹�����̂�map�Ɠ���width * height �̈ꎟ���z��̕����悳����
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