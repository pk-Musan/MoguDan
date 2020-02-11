#pragma once

#include "DangeonRectangle.h"

class DangeonDivision {

private:
	DangeonRectangle outer; // 区画の外側
	DangeonRectangle inner; // 区画の内側（部屋の矩形）
};