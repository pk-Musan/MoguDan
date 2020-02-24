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
	inputKey();

	/*
		// 移動系
		if ( KeyBoard.key[KEYINPUT_LEFT] == 1 ) {
			player->state = MOVE_BEGIN;
			player->direction = Player::LEFT;
		} else if () {
			
		}
		// 攻撃系
		else if ( KeyeBoard.key[KEYINPUT_SPACE] == 1 ) player->state = ATTACK_BEGIN;
		// その他諸々
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
	playerのstateがキー入力待ちの場合，キー入力を受けてplayerのstateを変更
*/
void DungeonLayerManager::inputKey() {
	if ( player->getState() != Player::State::KEY_INPUT ) return;

	// メニュー画面を開いてないとき
	// if (  )

	// 方向転換，移動
	if ( KeyBoard::key[KEY_INPUT_LEFT] >= 1 && KeyBoard::key[KEY_INPUT_UP] >= 1 ) {
		player->setDirection( Player::Direction::LEFT_UP );
		if ( KeyBoard::key[KEY_INPUT_LSHIFT] == 0 ) player->setState( Player::State::MOVE_BEGIN );
		return;
	} else if ( KeyBoard::key[KEY_INPUT_RIGHT] >= 1 && KeyBoard::key[KEY_INPUT_UP] >= 1 ) {
		player->setDirection( Player::Direction::RIGHT_UP );
		if ( KeyBoard::key[KEY_INPUT_LSHIFT] == 0 ) player->setState( Player::State::MOVE_BEGIN );
		return;
	} else if ( KeyBoard::key[KEY_INPUT_RIGHT] >= 1 && KeyBoard::key[KEY_INPUT_DOWN] >= 1 ) {
		player->setDirection( Player::Direction::RIGHT_DOWN );
		if ( KeyBoard::key[KEY_INPUT_LSHIFT] == 0 ) player->setState( Player::State::MOVE_BEGIN );
		return;
	} else if ( KeyBoard::key[KEY_INPUT_LEFT] >= 1 && KeyBoard::key[KEY_INPUT_DOWN] >= 1 ) {
		player->setDirection( Player::Direction::LEFT_DOWN );
		if ( KeyBoard::key[KEY_INPUT_LSHIFT] == 0 ) player->setState( Player::State::MOVE_BEGIN );
		return;
	} 
	else if ( KeyBoard::key[KEY_INPUT_LEFT] >= 1 ) {
		player->setDirection( Player::Direction::LEFT );
		if ( KeyBoard::key[KEY_INPUT_LSHIFT] == 0 ) player->setState( Player::State::MOVE_BEGIN );
		return;
	} else if ( KeyBoard::key[KEY_INPUT_UP] >= 1 ) {
		player->setDirection( Player::Direction::UP );
		if ( KeyBoard::key[KEY_INPUT_LSHIFT] == 0 ) player->setState( Player::State::MOVE_BEGIN );
		return;
	} else if ( KeyBoard::key[KEY_INPUT_RIGHT] >= 1 ) {
		player->setDirection( Player::Direction::RIGHT );
		if ( KeyBoard::key[KEY_INPUT_LSHIFT] == 0 ) player->setState( Player::State::MOVE_BEGIN );
		return;
	} else if ( KeyBoard::key[KEY_INPUT_DOWN] >= 1 ) {
		player->setDirection( Player::Direction::DOWN );
		if ( KeyBoard::key[KEY_INPUT_LSHIFT] == 0 ) player->setState( Player::State::MOVE_BEGIN );
		return;
	}

	/*
	if ( KeyBoard::key[KEY_INPUT_SPACE] == 1 ) {
		player->setState( Actor::State::ATTACK_BEGIN );
	}
	*/
}



void DungeonLayerManager::move() {
	if ( player->getState() == Player::State::MOVE_BEGIN ) {
		// 移動可能か判定
		int dx, dy;
		int dir = player->getDirection();

		if ( dir == Player::LEFT || dir == Player::LEFT_UP || dir == Player::LEFT_DOWN ) dx = -1;
		else if ( dir == Player::UP || dir == Player::DOWN ) dx = 0;
		else if ( dir == Player::RIGHT_UP || dir == Player::RIGHT || dir == Player::RIGHT_DOWN ) dx = 1;
		
		if ( dir == Player::LEFT_UP || dir == Player::UP || dir == Player::RIGHT_UP ) dy = -1;
		else if ( dir == Player::LEFT || dir == Player::RIGHT ) dy = 0;
		else if ( dir == Player::RIGHT_DOWN || dir == Player::DOWN || dir == Player::LEFT_DOWN ) dy = 1;

		if ( dungeonLayer->isFloor( player->getX() + dx, player->getY() + dy ) ) {
			player->move( dx, dy );
			player->setState( Player::State::MOVE );
		} else player->setState( Player::State::KEY_INPUT );
	}
	
	/*
	if ( player->getState() == Player::State::MOVE || player->getState() == Player::State::ATTACK_END || ~  ) return;
	for ( Enemy* enemy : enemies ) {
		if ( enemy->getState() == Enemy::State::MOVE_BEGIN ) {
			// playerとダンジョンの参照を渡して敵ごとに移動を決定する
			enemy->move( player, dungeonLayer );

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