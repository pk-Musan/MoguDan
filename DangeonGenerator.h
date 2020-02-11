#pragma once

#include "Layer2D.h"
#include "DangeonDivision.h"

#include <list>

class DangeonGenerator {

private:
	Layer2D layer; // ある階層のデータ，幅，高さなどを管理
	std::list<DangeonDivision> divisions; // ある階層に存在する区画（部屋）
};