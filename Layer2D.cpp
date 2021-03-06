#include "Layer2D.h"

// createLayer() を使ってdataを初期化
Layer2D::Layer2D( int width, int height ) : width(0), height(0), data(0) {
}

Layer2D::~Layer2D() {
	printfDx( "~Layer2D : start\n" );
	delete[] data;
	data = 0;
	printfDx( "~Layer2D : end\n" );
}

int& Layer2D::operator()( int y, int x ) {
	return data[y * width + x];
}

const int& Layer2D::operator()( int y, int x ) const {
	return data[y * width + x];
}

/*
	dataが確保している領域をdeleteしてから
	dataをwidth * height分のint型配列として初期化
*/
void Layer2D::createLayer( int width, int height ) {
	delete data;
	data = 0;

	this->width = width;
	this->height = height;
	data = new int[width * height];
}

// 領域外かどうかチェック（領域外ならtrueを返す）
bool Layer2D::isOutOfRange( int y, int x ) {
	if ( y < 0 || y >= height ) return true;
	if ( x < 0 || x >= width ) return true;
	
	return false;
}

// dataをvalで埋める
void Layer2D::fill( int val ) {
	for ( int y = 0; y < height; y++ ) {
		for ( int x = 0; x < width; x++ ) {
			data[y * width + x] = val;
		}
	}
}

// (y, x)からx方向にw分，y方向にh分の範囲でdataをvalで埋める
void Layer2D::fillRect( int x, int y, int w, int h, int val ) {
	for ( int Y = y; Y < y + h; Y++ ) {
		for ( int X = x; X < x + w; X++ ) {
			if ( isOutOfRange( Y, X ) ) continue;

			data[Y * width + X] = val;
		}
	}
}

void Layer2D::fillRectLTRB( int left, int top, int right, int bottom, int val ) {
	fillRect( left, top, right - left + 1, bottom - top + 1, val );
}

// ある層のマップデータ確認用
void Layer2D::Dump() {
	for ( int y = 0; y < height; y++ ) {
		for ( int x = 0; x < width; x++ ) {
			if ( data[y * width + x] == 0 )	printfDx( "　" );
			else if ( data[y * width + x] == 1 ) printfDx( "＃" );
			else if ( data[y * width + x] == 2 ) printfDx( "＄" );
		}
		printfDx( "\n" );
	}
}