#pragma once

//#include "DangeonRectangle.h"

class DangeonDivision {
public:
	class DangeonRectangle {

	public:
		int left; // 区画の左端
		int top; // 区画の上端
		int right; // 区画の右端
		int bottom; // 区画の下端

	public:
		DangeonRectangle();
		void set( int left, int top, int right, int bottom );
		int getWidth() const { return right - left + 1; }
		int getHeight() const { return bottom - top + 1; }
	};

public:
	DangeonRectangle outer; // 区画の外側
	DangeonRectangle inner; // 区画の内側（部屋の矩形）

public:
	DangeonDivision();
	~DangeonDivision();
	//int calcOuterArea() const { return outer.getHeight() * outer.getWidth(); }
	//int calcInnerArea() const { return inner.getHeight() * inner.getWidth(); }
	
	//bool operator<( const DangeonDivision& anotherDiv ) const;
};