#pragma once

/*
	�v���C���[��G�Ȃǂ̊�b�N���X
*/
class Actor {
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

private:
	int x; // �L�����N�^��x���W
	int y; // �L�����N�^��y���W
	int maxHp; // �L�����N�^�̍ő�HP
	int maxMp; // �L�����N�^�̍ő�MP
	int hp; // �L�����N�^�̌��݂�HP
	int mp; // �L�����N�^�̌��݂�MP
	int strength; // �L�����N�^�̍U����
	int defense; // �L�����N�^�̖h���

public:
	Actor( int x, int y, int maxHp, int maxMp, int strength, int defense );
	virtual ~Actor();

	// �X�e�[�^�X��getter
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