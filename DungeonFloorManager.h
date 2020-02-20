#pragma once
#include "DungeonGenerator.h"
#include "Player.h"

/*
	DungeonGenerator�N���X�ɂ���Ď����������ꂽ�t���A�ƃv���C���[�C�A�C�e���C�G�Ȃǂ̃C���X�^���X���Ǘ�����
*/

class DungeonFloorManager {
private:
	int width, height; // �_���W�����̕��ƍ���
	DungeonGenerator* dungeonGenerator; // �_���W����������
	Layer2D* map; // ���݂���t���A�̎��f�[�^
	std::list<DungeonDivision*>* divisions; // ���݂���t���A�̋����
	Player player; // �v���C���[
	// item��map���ƏƂ炵���킹�����̂�map�Ɠ���width * height �̈ꎟ���z��̕����悳����
	// std::vector<Item*> items;
	// std::vector<Enemy*> enemies;

public:
	DungeonFloorManager( int width, int height );
	~DungeonFloorManager();

	void generateFloor();
	void setPlayerPosition();
};