#include "DangeonDivision.h"

DangeonDivision::DangeonRectangle::DangeonRectangle() {
	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}

// ���̍��[�C��[�C�E�[�C���[���Z�b�g����
void DangeonDivision::DangeonRectangle::set( int left, int top, int right, int bottom ) {
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

DangeonDivision::DangeonDivision() {
	//outer = new DangeonRectangle();
	//inner = new DangeonRectangle();
}

DangeonDivision::~DangeonDivision() {
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