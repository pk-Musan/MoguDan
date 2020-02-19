#pragma once

//#include "DangeonRectangle.h"

class DungeonDivision {
public:
	class DungeonRectangle {

	public:
		int left; // ���̍��[
		int top; // ���̏�[
		int right; // ���̉E�[
		int bottom; // ���̉��[

	public:
		DungeonRectangle();
		void set( int left, int top, int right, int bottom );
		int getWidth() const { return right - left + 1; }
		int getHeight() const { return bottom - top + 1; }
	};

public:
	DungeonRectangle outer; // ���̊O��
	DungeonRectangle inner; // ���̓����i�����̋�`�j

public:
	DungeonDivision();
	~DungeonDivision();
	//int calcOuterArea() const { return outer.getHeight() * outer.getWidth(); }
	//int calcInnerArea() const { return inner.getHeight() * inner.getWidth(); }
	
	//bool operator<( const DangeonDivision& anotherDiv ) const;
};