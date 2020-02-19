#pragma once

#include "Layer2D.h"
#include "DungeonDivision.h"

#include <list>
#include <vector>

class DungeonGenerator {

public:
	static const int MIN_ROOM_SIZE = 4; // �����̍ŏ���(����)
	//static const int MAX_ROOM_SIZE = 
	static const int OUTER_MERGIN = 2; // �ʘH�p�Ɏc���Ă���������
	static const int MAX_ROOM_NUM = 21; // 1�t���A���ɂ��镔�����̍ő吔
	static const int MIN_ROOM_NUM = 2; // 1�t���A���ɂ��镔�����̍ŏ���

	int roomNum; // ������

private:
	int width, height; // �_���W�����̕��ƍ���
	Layer2D layer; // ����K�w�̃f�[�^�C���C�����Ȃǂ��Ǘ�
	std::list<DungeonDivision*> divisions; // ����K�w�ɑ��݂�����i�����j

public:
	DungeonGenerator( int width, int height );
	~DungeonGenerator();

	bool checkDivisionSize( int size );

	void generate();
	void createDivision( int left, int top, int right, int bottom );
	void splitDivison( bool vertical );
	void createRoom();
	void fillRoom( DungeonDivision::DungeonRectangle inner );
	void sortDivisionByArea();
	void createRoute();
	void connectRoute();
	void searchKnot( int from, int to, int fixedPoint, bool vertical, std::vector<int>& knots );
};