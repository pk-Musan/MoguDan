#pragma once

#include "Layer2D.h"
#include "DangeonDivision.h"

#include <list>

class DangeonGenerator {

private:
	int width, height; // �_���W�����̕��ƍ���
	Layer2D* layer; // ����K�w�̃f�[�^�C���C�����Ȃǂ��Ǘ�
	std::list<DangeonDivision*> divisions; // ����K�w�ɑ��݂�����i�����j

public:
	DangeonGenerator( int width, int height );
	~DangeonGenerator();

	bool checkDivisionWidth( int width );
	bool checkDivisionHeight( int height );

	void generate();
	void createDivision( int left, int top, int right, int bottom );
	void splitDivison( bool vertical );
	void createRoom();
	void createRoute();
};