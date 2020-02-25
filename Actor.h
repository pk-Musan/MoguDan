#pragma once

/*
	�v���C���[��G�Ȃǂ̊�b�N���X
*/
class Actor {
public:
	// �L�����N�^�̏��
	enum State {
		// ���͑҂�
		KEY_INPUT,

		// �U���n�߂���I���܂�
		ATTACK_BEGIN,
		ATTACK,
		ATTACK_END,

		// �ړ��n�߂���I���܂�
		MOVE_BEGIN,
		MOVE,
		MOVE_END,

		// �s���I��
		TURN_END
	};
	
	// �L�����N�^�̌���
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
		DEFAULT, // �ʏ�A�j���[�V����
		MOVE, // �ړ��A�j���[�V����
		ATTACK, // �U���A�j���[�V����
		ATTACKED, // ��U���A�j���[�V����
		TRAPPED, // 㩍쓮���A�j���[�V����
		DEAD // ���S���A�j���[�V����
	};

private:
	int x; // �L�����N�^��x���W
	int y; // �L�����N�^��y���W
	int maxHp; // �L�����N�^�̍ő�HP
	int maxMp; // �L�����N�^�̍ő�MP
	int hp; // �L�����N�^�̌��݂�HP
	int mp; // �L�����N�^�̌��݂�MP
	int attack; // �L�����N�^�̍U����
	int defense; // �L�����N�^�̖h���
	int evasion; // �L�����N�^�̉��
	int speed; // �L�����N�^�̑����i1�Ȃ�1�^�[����1��s���C2�Ȃ�1�^�[����2��s���j

	State state;
	Direction direction;
	AnimationState animeState;

	int animationCount;

public:
	Actor( int x, int y, int maxHp, int maxMp, int strength, int defense, int evasion, int speed );
	virtual ~Actor();

	// �X�e�[�^�X��getter
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