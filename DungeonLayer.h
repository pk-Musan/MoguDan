#pragma once
#include "Layer2D.h"
#include "DungeonDivision.h"

#include <list>
#include <vector>
#include <time.h>
#include <algorithm>

class DungeonLayer {

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
	DungeonLayer( int width, int height );
	~DungeonLayer();

	// DungeonGenerator�Ő��������t���A�f�[�^��DungeonFloorManager�ɂ킽��
	Layer2D* getLayer() { return &layer; }
	// DungeonGenerator�Ő��������t���A�̋�����DungeonFloorManager�ɂ킽��
	std::list<DungeonDivision*>* getDivisions() { return &divisions; }

	
	void generate();
	void createDivision( int left, int top, int right, int bottom );
	void splitDivison( bool vertical );
	bool checkDivisionSize( int size );
	void createRoom();
	void fillRoom( DungeonDivision::DungeonRectangle inner );
	void sortDivisionByArea();
	void createRoute();
	void connectRoute();
	void searchKnot( int from, int to, int fixedPoint, bool vertical, std::vector<int>& knots );

	inline bool isFloor( int x, int y ) { return ( layer( y, x ) == 0 ); }
	void setRandomPointInRoom( int& x, int& y );
	void setRandomPointInLayer( int& x, int& y );
};