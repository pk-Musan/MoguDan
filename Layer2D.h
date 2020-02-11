#pragma once

class Layer2D {

private:
	int width; // ‚ ‚éŠK‘w‚Ì•
	int height; // ‚ ‚éŠK‘w‚Ì‚‚³
	int* data = 0; // ‚ ‚éŠK‘w‚Ìƒf[ƒ^

public:
	Layer2D( int width = 0, int height = 0 );

	int getWidth() { return width; }
	int getHeight() { return height; }
	int& operator()( int y, int x ) { return data[y * width + x]; }
	const int& operator()( int y, int x ) const { return data[y * width + x]; }

	void createLayer( int width, int height );
	bool isOutOfRange( int y, int x );
	void fill( int val );
	void fillRect( int x, int y, int w, int h, int val );

	void Dump();
};