#pragma once

#include "Layer2D.h"
#include "DangeonDivision.h"

#include <list>

class DangeonGenerator {

public:
	static const int MIN_ROOM_SIZE = 3; // �����̍ŏ���(����)
	static const int OUTER_MERGIN = 1; // �ʘH�p�Ɏc���Ă���������
	static const int MAX_ROOM_NUM = 18; // 1�t���A���ɂ��镔�����̍ő吔
	static const int MIN_ROOM_NUM = 2; // 1�t���A���ɂ��镔�����̍ŏ���

	int roomNum; // ������

private:
	int width, height; // �_���W�����̕��ƍ���
	Layer2D* layer; // ����K�w�̃f�[�^�C���C�����Ȃǂ��Ǘ�
	std::list<DangeonDivision*> divisions; // ����K�w�ɑ��݂�����i�����j

public:
	DangeonGenerator( int width, int height );
	~DangeonGenerator();

	bool checkDivisionSize( int size );

	void generate();
	void createDivision( int left, int top, int right, int bottom );
	void splitDivison( bool vertical );
	void createRoom();
	void createRoute();
};