#pragma once

#include "Layer2D.h"
#include "DangeonDivision.h"

#include <list>

class DangeonGenerator {

private:
	int width, height; // ダンジョンの幅と高さ
	Layer2D* layer; // ある階層のデータ，幅，高さなどを管理
	std::list<DangeonDivision*> divisions; // ある階層に存在する区画（部屋）

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