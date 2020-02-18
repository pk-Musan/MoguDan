#pragma once

//#include "DangeonRectangle.h"

class DangeonDivision {
public:
	class DangeonRectangle {

	public:
		int left; // ���̍��[
		int top; // ���̏�[
		int right; // ���̉E�[
		int bottom; // ���̉��[

	public:
		DangeonRectangle();
		void set( int left, int top, int right, int bottom );
		int getWidth() const { return right - left + 1; }
		int getHeight() const { return bottom - top + 1; }
	};

public:
	DangeonRectangle outer; // ���̊O��
	DangeonRectangle inner; // ���̓����i�����̋�`�j

public:
	DangeonDivision();
	~DangeonDivision();
	//int calcOuterArea() const { return outer.getHeight() * outer.getWidth(); }
	//int calcInnerArea() const { return inner.getHeight() * inner.getWidth(); }
	
	//bool operator<( const DangeonDivision& anotherDiv ) const;
};