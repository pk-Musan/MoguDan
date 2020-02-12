#include "DxLib.h"
#include "DangeonGenerator.h"
#include "KeyBoard.h"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow ) {
	int frameStartTime;

	ChangeWindowMode( TRUE );

	SetGraphMode( 640, 480, 32 );

	if ( DxLib_Init() == -1 ) {
		return -1;
	}

	SetDrawScreen( DX_SCREEN_BACK );
	SetWaitVSyncFlag( FALSE );

	frameStartTime = GetNowCount();
	DangeonGenerator dg( 5, 6 );
	dg.generate();

	while ( ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && KeyBoard::updateKey() == 0 ) { // 画面更新 & メッセージ処理 & 画面消去
		while ( GetNowCount() - frameStartTime < 1000 / 60 ) {}

		frameStartTime = GetNowCount();

		if ( KeyBoard::key[KEY_INPUT_Q] == 1 ) break;
	}

	WaitKey();

	DxLib_End();

	return 0;
}