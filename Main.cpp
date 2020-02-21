#include "DxLib.h"
#include "DungeonLayerManager.h"
#include "KeyBoard.h"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow ) {
	int loopStartTime;
	int generateStartTime;

	ChangeWindowMode( TRUE );

	SetGraphMode( 1120, 960, 32 );

	if ( DxLib_Init() == -1 ) {
		return -1;
	}

	SetDrawScreen( DX_SCREEN_BACK );
	SetWaitVSyncFlag( FALSE );

	loopStartTime = GetNowCount();
	DungeonLayerManager* dgLayerManager = new DungeonLayerManager( 55, 55 );
	generateStartTime = GetNowCount();
	dgLayerManager->generateLayer();
	printfDx( "time = %d\n", GetNowCount() - generateStartTime );

	while ( ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && KeyBoard::updateKey() == 0 ) { // 画面更新 & メッセージ処理 & 画面消去
		while ( GetNowCount() - loopStartTime < 1000 / 60 ) {}

		loopStartTime = GetNowCount();

		//if ( KeyBoard::key[KEY_INPUT_Q] == 1 ) break;
		if ( KeyBoard::key[KEY_INPUT_Q] == 1 ) {
			clsDx();
			delete dgLayerManager;
			dgLayerManager = 0;
		}
		if ( KeyBoard::key[KEY_INPUT_ESCAPE] == 1 ) {
			delete dgLayerManager;
			dgLayerManager = 0;
			break;
		}
		if ( KeyBoard::key[KEY_INPUT_SPACE] == 1 ) {
			generateStartTime = GetNowCount();
			if ( dgLayerManager == nullptr ) {
				clsDx();
				dgLayerManager = new DungeonLayerManager( 55, 55 );
				dgLayerManager->generateLayer();
				printfDx( "time = %d\n", GetNowCount() - generateStartTime );
			} else {
				clsDx();
				dgLayerManager->generateLayer();
				printfDx( "time = %d\n", GetNowCount() - generateStartTime );
			}
		}
	}

	DxLib_End();

	return 0;
}