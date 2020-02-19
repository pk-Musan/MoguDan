#pragma once

//#include "DangeonRectangle.h"

class DungeonDivision {
public:
	class DungeonRectangle {

	public:
		int left; // 区画の左端
		int top; // 区画の上端
		int right; // 区画の右端
		int bottom; // 区画の下端

	public:
		DungeonRectangle();
		void set( int left, int top, int right, int bottom );
		int getWidth() const { return right - left + 1; }
		int getHeight() const { return bottom - top + 1; }
	};

public:
	DungeonRectangle outer; // 区画の外側
	DungeonRectangle inner; // 区画の内側（部屋の矩形）

public:
	DungeonDivision();
	~DungeonDivision();
	//int calcOuterArea() const { return outer.getHeight() * outer.getWidth(); }
	//int calcInnerArea() const { return inner.getHeight() * inner.getWidth(); }
	
	//bool operator<( const DangeonDivision& anotherDiv ) const;
};