#pragma once

class DangeonRectangle {

private:
	int left; // ���̍��[
	int top; // ���̏�[
	int right; // ���̉E�[
	int bottom; // ���̉��[

public:
	void set( int left, int top, int right, int bottom );
	int getWidth() { return right - left + 1; }
	int getHeight() { return bottom - top + 1; }
};