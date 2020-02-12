#pragma once

//#include "DangeonRectangle.h"

class DangeonDivision {
	class DangeonRectangle {

	private:
		int left; // 区画の左端
		int top; // 区画の上端
		int right; // 区画の右端
		int bottom; // 区画の下端

	public:
		void set( int left, int top, int right, int bottom );
		int getWidth() { return right - left + 1; }
		int getHeight() { return bottom - top + 1; }
	};

public:
	DangeonRectangle* outer; // 区画の外側
	DangeonRectangle* inner; // 区画の内側（部屋の矩形）

public:
	DangeonDivision();
	~DangeonDivision();
};