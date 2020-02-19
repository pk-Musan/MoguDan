#include "DangeonRectangle.h"

// 区画の左端，上端，右端，下端をセットする
void DangeonRectangle::set( int left, int top, int right, int bottom ) {
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}