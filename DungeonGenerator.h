#pragma once

#include "Layer2D.h"
#include "DungeonDivision.h"

#include <list>
#include <vector>

class DungeonGenerator {

public:
	static const int MIN_ROOM_SIZE = 4; // 部屋の最小幅(高さ)
	//static const int MAX_ROOM_SIZE = 
	static const int OUTER_MERGIN = 2; // 通路用に残しておきたい幅
	static const int MAX_ROOM_NUM = 21; // 1フロア内にある部屋数の最大数
	static const int MIN_ROOM_NUM = 2; // 1フロア内にある部屋数の最小数

	int roomNum; // 部屋数

private:
	int width, height; // ダンジョンの幅と高さ
	Layer2D layer; // ある階層のデータ，幅，高さなどを管理
	std::list<DungeonDivision*> divisions; // ある階層に存在する区画（部屋）

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