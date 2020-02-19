#include "DungeonDivision.h"

DungeonDivision::DungeonRectangle::DungeonRectangle() {
	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}

// 区画の左端，上端，右端，下端をセットする
void DungeonDivision::DungeonRectangle::set( int left, int top, int right, int bottom ) {
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

DungeonDivision::DungeonDivision() {
	//outer = new DangeonRectangle();
	//inner = new DangeonRectangle();
}

DungeonDivision::~DungeonDivision() {
	/*
	delete outer;
	delete inner;

	outer = 0;
	inner = 0;
	*/
}
/*
bool DangeonDivision::operator<( const DangeonDivision& anotherDiv ) const {
	return this->calcOuterArea() > anotherDiv.calcOuterArea();
}
*/