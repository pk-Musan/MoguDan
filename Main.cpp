#include "DxLib.h"
#include "DungeonFloorManager.h"
#include "KeyBoard.h"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow ) {
	int loopStartTime;
	int generateStartTime;

	ChangeWindowMode( TRUE );

	SetGraphMode( 960, 960, 32 );

	if ( DxLib_Init() == -1 ) {
		return -1;
	}

	SetDrawScreen( DX_SCREEN_BACK );
	SetWaitVSyncFlag( FALSE );

	loopStartTime = GetNowCount();
	DungeonFloorManager* dgfloorManager = new DungeonFloorManager( 50, 50 );
	generateStartTime = GetNowCount();
	dgfloorManager->generateFloor();
	printfDx( "time = %d\n", GetNowCount() - generateStartTime );

	while ( ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && KeyBoard::updateKey() == 0 ) { // 画面更新 & メッセージ処理 & 画面消去
		while ( GetNowCount() - loopStartTime < 1000 / 60 ) {}

		loopStartTime = GetNowCount();

		//if ( KeyBoard::key[KEY_INPUT_Q] == 1 ) break;
		if ( KeyBoard::key[KEY_INPUT_Q] == 1 ) {
			clsDx();
			delete dgfloorManager;
			dgfloorManager = 0;
		}
		if ( KeyBoard::key[KEY_INPUT_ESCAPE] == 1 ) {
			delete dgfloorManager;
			dgfloorManager = 0;
			break;
		}
		if ( KeyBoard::key[KEY_INPUT_SPACE] == 1 ) {
			generateStartTime = GetNowCount();
			if ( dgfloorManager == nullptr ) {
				clsDx();
				dgfloorManager = new DungeonFloorManager( 50, 50 );
				dgfloorManager->generateFloor();
				printfDx( "time = %d\n", GetNowCount() - generateStartTime );
			} else {
				clsDx();
				dgfloorManager->generateFloor();
				printfDx( "time = %d\n", GetNowCount() - generateStartTime );
			}
		}
	}

	DxLib_End();

	return 0;
}