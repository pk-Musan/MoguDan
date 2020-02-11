#pragma once

#include "Layer2D.h"
#include "DangeonDivision.h"

#include <list>

class DangeonGenerator {

private:
	Layer2D layer; // ����K�w�̃f�[�^�C���C�����Ȃǂ��Ǘ�
	std::list<DangeonDivision> divisions; // ����K�w�ɑ��݂�����i�����j
};