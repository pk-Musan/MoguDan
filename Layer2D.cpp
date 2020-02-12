#include "Layer2D.h"
#include "DxLib.h"

// createLayer() ���g����data��������
Layer2D::Layer2D( int width, int height ) : width(0), height(0), data(0) {
	if ( width > 0 && height > 0 ) {
		createLayer( width, height );
	}
}

/*
int& Layer2D::operator()( int y, int x ) {
	return data[y * width + x];
}

const int& Layer2D::operator()( int y, int x ) const {
	return data[y * width + x];
}
*/

// data��width * height����int�^�z��Ƃ��ď�����
void Layer2D::createLayer( int width, int height ) {
	this->width = width;
	this->height = height;
	data = new int[width * height];
}

// �̈�O���ǂ����`�F�b�N�i�̈�O�Ȃ�true��Ԃ��j
bool Layer2D::isOutOfRange( int y, int x ) {
	if ( y < 0 || y >= height ) return true;
	if ( x < 0 || x >= width ) return true;
	
	return false;
}

// data��val�Ŗ��߂�
void Layer2D::fill( int val ) {
	for ( int y = 0; y < height; y++ ) {
		for ( int x = 0; x < width; x++ ) {
			data[y * width + x] = val;
		}
	}
}

// (y, x)����x������w���Cy������h���͈̔͂�data��val�Ŗ��߂�
void Layer2D::fillRect( int x, int y, int w, int h, int val ) {
	for ( int Y = y; Y < y + h; Y++ ) {
		for ( int X = x; X < x + w; X++ ) {
			if ( isOutOfRange( Y, X ) ) continue;

			data[Y * width + X] = val;
		}
	}
}

// ����w�̃}�b�v�f�[�^�m�F�p
void Layer2D::Dump() {
	for ( int y = 0; y < height; y++ ) {
		for ( int x = 0; x < width; x++ ) {
			printfDx( "%d ", data[y * width + x] );
		}
		printfDx( "\n" );
	}
}