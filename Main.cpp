#include "DxLib.h"
#include "Layer2D.h"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow ) {
	if ( DxLib_Init() == -1 ) {
		return -1;
	}

	//DrawPixel( 320, 240, GetColor( 255, 255, 255 ) );
	Layer2D layer( 4, 5 );
	layer.fill( 1 );
	layer.fillRect( 1, 1, 4, 3, 5 );
	layer.Dump();

	WaitKey();

	DxLib_End();

	return 0;
}