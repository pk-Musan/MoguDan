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
		�K�i�Ƃ�㩂�ݒu
	*/

	/*
		�A�C�e���𐶐�����
	*/

	/*
		player�̈ʒu�������_���Ɍ��߂ăZ�b�g������
	*/
	if ( player == nullptr ) initPlayerInfo();
	else setPlayerPosition();
}


/*
	�����_���Ɉʒu�����肵�ăv���C���[��������
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
	�_���W�����������Ƀv���C���[�̈ʒu�������_���Ɍ��肵�ăv���C���[�̍��W�Ɋi�[����
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
	// ���ׂẴL�����N�^��TURN_END�ł���΃v���C���[���L�[���͑҂��ɕύX

	// �v���C���[�̏�Ԃ��L�[���͑҂��ł���΃L�[���͂��󂯂�
	/*
		if ( KeyeBoard.key[KEYINPUT_SPACE] == 1 ) player->state = ATTACK_BEGIN;
		else if ()
	*/


	// �v���C���[��MOVE�QBEGIN
	// draw�֐����ňړ����̕`�悪�I��������Ԃ�MOVE_END�Ɉڍs����
	/*
		�ړ��\������

		player->move() // ���W���X�V�C�ǂ̕������痈�����L�������Ă���

		�v���C���[�̈ړ���ɍ��킹�Ċe�G�̍s��������

		// �G�̈ړ������s
		for ( Enemy* enemy : enemies ) {
			if ( enemy->state == enemy->MOVE_BEGIN ) {
				enemy->state = enemy->MOVE;
				enemy->move()
			}
		}
	*/


	// �v���C���[��ATTACK_END && �U�����̓G�����Ȃ�
	// draw�֐����ňړ����̕`�悪�I��������Ԃ�MOVE_END�Ɉڍs����
	/*
		// �G�̈ړ������s
		for ( Enemy* enemy : enemies ) {
			if ( enemy->state == enemy->MOVE_BEGIN ) {
				enemy->state = enemy->MOVE;
				enemy->move()
			}
		}
	*/


	// draw�֐����ōU���p�̃A�j���[�V�������I�������v���C���[�̏�Ԃ�ATTACK�Ɉڍs
	// �v���C���[��ATTACK�̏ꍇ
	/*
		// �v���C���[�̈ʒu�}�X��ɓG�܂���㩂��Ȃ����`�F�b�N
		// �G������ꍇ�Cplayer->attack( enemy );
		// �U���Ώ�enemy�̗̑̓`�F�b�N
		// �̗͂�0�ȉ��̏ꍇ��enemy�̏�Ԃ�DEAD�QBEGIN�ɕύX
		// 㩂�����ꍇ��㩂̏�Ԃ�visible�ɕύX
		// �v���C���[�̏�Ԃ�ATTACK�QEND�Ɉڍs
	*/


	// �v���C���[��MOVE_END���ړ���(MOVE)�̓G�����Ȃ� or �v���C���[��ATTACK_END
	// �v���C���[�ɑ΂��čU����(ATTACK)�̓G�����Ȃ��C�����S�A�j���[�V�������̓G�����Ȃ�
	/*
		// attackByEnemy() �Ƃ��̊֐��ɂ���
		// �܂��v���C���[�̗̑͂̊m�F
		// �̗͂�0�ȉ��̏ꍇ�̓v���C���[�̏�Ԃ�DEAD�ɕύX����return

		// �v���C���[�ɑ΂���1�̂��U�������s
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
	�}�b�v�C�A�C�e���C�v���C���[�C�G�̕`��
*/
void DungeonLayerManager::draw() {
	/*
		map�̕`��
		dungeonLayer->draw();
	*/

	/*
		�A�C�e���̕`��
		for ( Item* item : items ) item->draw();
	*/

	/*
		�v���C���[�̕`��
		player->draw();
	*/

	/*
		�G�̕`��
		for ( Enemy* enemy : enemies ) enemy->draw();
	*/
}