#include "DangeonDivision.h"

// 区画の左端，上端，右端，下端をセットする
void DangeonDivision::DangeonRectangle::set( int left, int top, int right, int bottom ) {
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

DangeonDivision::DangeonDivision() {
	outer = new DangeonRectangle();
	inner = new DangeonRectangle();
}

DangeonDivision::~DangeonDivision() {
	delete outer;
	delete inner;

	outer = 0;
	inner = 0;
}