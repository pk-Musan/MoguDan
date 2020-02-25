#pragma once

/*
	プレイヤーや敵などの基礎クラス
*/
class Actor {
public:
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

	enum AnimationState {
		DEFAULT, // 通常アニメーション
		MOVE, // 移動アニメーション
		ATTACK, // 攻撃アニメーション
		ATTACKED, // 被攻撃アニメーション
		TRAPPED, // 罠作動時アニメーション
		DEAD // 死亡時アニメーション
	};

private:
	int x; // キャラクタのx座標
	int y; // キャラクタのy座標
	int maxHp; // キャラクタの最大HP
	int maxMp; // キャラクタの最大MP
	int hp; // キャラクタの現在のHP
	int mp; // キャラクタの現在のMP
	int attack; // キャラクタの攻撃力
	int defense; // キャラクタの防御力
	int evasion; // キャラクタの回避率
	int speed; // キャラクタの速さ（1なら1ターンに1回行動，2なら1ターンに2回行動）

	State state;
	Direction direction;
	AnimationState animeState;

	int animationCount;

public:
	Actor( int x, int y, int maxHp, int maxMp, int strength, int defense, int evasion, int speed );
	virtual ~Actor();

	// ステータスのgetter
	const int getX() const { return x; }
	const int getY() const { return y; }
	const int getMaxHp() const { return maxHp; }
	const int getMaxMp() const { return maxMp; }
	const int getHp() const { return hp; }
	const int getMp() const { return mp; }
	const int getAttack() const { return attack; }
	const int getDefense() const { return defense; }
	const int getEvasion() const { return evasion; }
	const int getSpeed() const { return speed; }

	const State getState() const { return state; }
	const Direction getDirection() const { return direction; }
	const AnimationState getAnimeState() const { return animeState; }

	void setPosition( int x, int y );
	
	void setState( State state );
	void setDirection( Direction direction );
	void setAnimeState( AnimationState animeState );

	void move( int dx, int dy );


	void draw();
};