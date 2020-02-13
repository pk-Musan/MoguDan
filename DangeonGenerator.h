#pragma once

#include "Layer2D.h"
#include "DangeonDivision.h"

#include <list>

class DangeonGenerator {

public:
	static const int MIN_ROOM_SIZE = 3; // 部屋の最小幅(高さ)
	static const int OUTER_MERGIN = 1; // 通路用に残しておきたい幅
	static const int MAX_ROOM_NUM = 18; // 1フロア内にある部屋数の最大数
	static const int MIN_ROOM_NUM = 2; // 1フロア内にある部屋数の最小数

	int roomNum; // 部屋数

private:
	int width, height; // ダンジョンの幅と高さ
	Layer2D* layer; // ある階層のデータ，幅，高さなどを管理
	std::list<DangeonDivision*> divisions; // ある階層に存在する区画（部屋）

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