#include "DungeonLayerManager.h"

DungeonLayerManager::DungeonLayerManager( int width, int height ) : width( width ), height( height ), player( 0 ) {
	dungeonLayer = new DungeonLayer( width, height );
}

DungeonLayerManager::~DungeonLayerManager() {
	printfDx( "~DngeonFloorManager : start\n" );
	delete dungeonLayer;
	dungeonLayer = 0;
	printfDx( "~DngeonFloorManager : end\n" );
}

void DungeonLayerManager::generateLayer() {
	dungeonLayer->generate();

	/*
		階段とか罠を設置
	*/

	/*
		アイテムを生成する
	*/

	/*
		playerの位置をランダムに決めてセットしたい
	*/
	if ( player == nullptr ) initPlayerInfo();
	else setPlayerPosition();
}


/*
	ランダムに位置を決定してプレイヤーを初期化
*/
void DungeonLayerManager::initPlayerInfo() {
	int x, y;
	dungeonLayer->setRandomPointInRoom( x, y );

	int maxHp = player->INITIAL_MAX_HP;
	int maxMp = player->INITIAL_MAX_MP;
	int attack = player->INITIAL_ATTACK;
	int defense = player->INITIAL_DEFENSE;
	int evasion = player->INITIAL_EVASION;
	int speed = player->INITIAL_SPEED;

	player = new Player( x, y, maxHp, maxMp, attack, defense, evasion, speed );
}

/*
	ダンジョン生成時にプレイヤーの位置をランダムに決定してプレイヤーの座標に格納する
*/
void DungeonLayerManager::setPlayerPosition() {
	int x, y;
	dungeonLayer->setRandomPointInRoom( x, y );
	player->setPosition( x, y );
}


void DungeonLayerManager::setEnemyPosition( /* Enemy& enemy */ ) {
	int x, y;
	do {
		dungeonLayer->setRandomPointInLayer( x, y );
	} while ( abs( player->getX() - x ) <= SPAWN_RANGE && abs( player->getY() - y ) <= SPAWN_RANGE );

	// enemy.setPosition( x, y );
}



void DungeonLayerManager::update() {
	// すべてのキャラクタがTURN_ENDであればプレイヤーをキー入力待ちに変更

	// プレイヤーの状態がキー入力待ちであればキー入力を受ける
	/*
		if ( KeyeBoard.key[KEYINPUT_SPACE] == 1 ) player->state = ATTACK_BEGIN;
		else if ()
	*/


	// プレイヤーがMOVE＿BEGIN
	// draw関数内で移動分の描画が終わったら状態をMOVE_ENDに移行する
	/*
		移動可能か判定

		player->move() // 座標を更新，どの方向から来たか記憶させておく

		プレイヤーの移動先に合わせて各敵の行動を決定

		// 敵の移動も実行
		for ( Enemy* enemy : enemies ) {
			if ( enemy->state == enemy->MOVE_BEGIN ) {
				enemy->state = enemy->MOVE;
				enemy->move()
			}
		}
	*/


	// プレイヤーがATTACK_END && 攻撃中の敵がいない
	// draw関数内で移動分の描画が終わったら状態をMOVE_ENDに移行する
	/*
		// 敵の移動も実行
		for ( Enemy* enemy : enemies ) {
			if ( enemy->state == enemy->MOVE_BEGIN ) {
				enemy->state = enemy->MOVE;
				enemy->move()
			}
		}
	*/


	// draw関数内で攻撃用のアニメーションが終わったらプレイヤーの状態をATTACKに移行
	// プレイヤーがATTACKの場合
	/*
		// プレイヤーの位置マス先に敵または罠がないかチェック
		// 敵がいる場合，player->attack( enemy );
		// 攻撃対象enemyの体力チェック
		// 体力が0以下の場合はenemyの状態をDEAD＿BEGINに変更
		// 罠がある場合は罠の状態をvisibleに変更
		// プレイヤーの状態をATTACK＿ENDに移行
	*/


	// プレイヤーがMOVE_ENDかつ移動中(MOVE)の敵がいない or プレイヤーがATTACK_END
	// プレイヤーに対して攻撃中(ATTACK)の敵がいない，かつ死亡アニメーション中の敵がいない
	/*
		// attackByEnemy() とかの関数にする
		// まずプレイヤーの体力の確認
		// 体力が0以下の場合はプレイヤーの状態をDEADに変更してreturn

		// プレイヤーに対して1体ずつ攻撃を実行
		for ( Enemy* enemy : enemies ) {
			if ( enemy->state == enemy->ATTACK_BEGIN ) {
				enemy->attack( player );
				enemy->state = ATTACK
				break;
			}
		}
	*/
}


/*
	マップ，アイテム，プレイヤー，敵の描画
*/
void DungeonLayerManager::draw() {
	/*
		mapの描画
		dungeonLayer->draw();
	*/

	/*
		アイテムの描画
		for ( Item* item : items ) item->draw();
	*/

	/*
		プレイヤーの描画
		player->draw();
	*/

	/*
		敵の描画
		for ( Enemy* enemy : enemies ) enemy->draw();
	*/
}