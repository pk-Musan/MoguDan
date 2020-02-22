#pragma once

/*
	プレイヤーや敵などの基礎クラス
*/
class Actor {
	// キャラクタの状態
	enum State {
		// 入力待ち
		KEY_INPUT,

		// 攻撃始めから終わりまで
		ATTACK_BEGIN,
		ATTACK,
		ATTACK_END,

		// 移動始めから終わりまで
		MOVE_BEGIN,
		MOVE,
		MOVE_END,

		// 行動終了
		TURN_END
	};
	
	// キャラクタの向き
	enum Direction {
		LEFT,
		LEFT_UP,
		UP,
		RIGHT_UP,
		RIGHT,
		RIGHT_DOWN,
		DOWN,
		LEFT_DOWN
	};

private:
	int x; // キャラクタのx座標
	int y; // キャラクタのy座標
	int maxHp; // キャラクタの最大HP
	int maxMp; // キャラクタの最大MP
	int hp; // キャラクタの現在のHP
	int mp; // キャラクタの現在のMP
	int strength; // キャラクタの攻撃力
	int defense; // キャラクタの防御力

public:
	Actor( int x, int y, int maxHp, int maxMp, int strength, int defense );
	virtual ~Actor();

	// ステータスのgetter
	const int getX() const { return x; }
	const int getY() const { return y; }
	const int getMaxHp() const { return maxHp; }
	const int getMaxMp() const { return maxMp; }
	const int getHp() const { return hp; }
	const int getMp() const { return mp; }
	const int getStrength() const { return strength; }
	const int getDefense() const { return defense; }

	void setPosition( int x, int y );
};