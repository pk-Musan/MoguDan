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
	inputKey();

	move();

	// �v���C���[��MOVE_END�̏ꍇ�C�G�̍U������ɑ����̊K�i�C�A�C�e���C㩂Ȃǂ̃`�F�b�N���s��
	// checkFloor() �ňȉ���3���s��
	// checkStairs();
	// checkFootingItem();
	// checkTrap();


	attackByPlayer();

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
	player��state���L�[���͑҂��̏ꍇ�C�L�[���͂��󂯂�player��state��ύX
*/
void DungeonLayerManager::inputKey() {
	if ( player->getState() != Player::State::KEY_INPUT ) return;

	// ���j���[��ʂ��J���ĂȂ��Ƃ�
	// if (  )

	// �����]���C�ړ�
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
	// Enter�F����ł̍U��
	// space�F���j���[���J��
	// c�F�Z�b�g�����A�C�e�����g���H
	if ( KeyBoard::key[KEY_INPUT_RETURN] == 1 ) {
		player->setState( Actor::State::ATTACK_BEGIN );
	}
	*/
}



void DungeonLayerManager::move() {
	if ( player->getState() == Player::State::MOVE_BEGIN ) {
		// �ړ��\������
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
	// �v���C���[��MOVE || ( �v���C���[��ATTACK_END && ATTACK�̓G�����Ȃ� )
	if ( !canEnemyMove() ) return;
	for ( Enemy* enemy : enemies ) {
		if ( enemy->getState() == Enemy::State::MOVE_BEGIN ) {
			// player�ƃ_���W�����̎Q�Ƃ�n���ēG���ƂɈړ������肷��
			// ���̏ꂩ�瓮���Ȃ��ꍇ�͏�Ԃ�MOVE_END�ɕύX
			enemy->move( player, dungeonLayer );
		}
	}
	*/
}


/*
	�G���ړ����s���Ă悢�����肷��
*/
bool DungeonLayerManager::canMoveEnemy() {
	if ( player->getState() == Player::State::MOVE ) return true;
	if ( player->getState() == Player::State::ATTACK_END ) {
		/*
		for ( Enemy* enemy : enemies ) {
			if ( enemy->getState() == Enemy::State::ATTACK || enemy->getState() == Enemy::State::ATTACK_BEGIN ) {
				return false;
			}
		}
		*/
		return true;
	}

	return false;
}



void DungeonLayerManager::attackByPlayer() {
	// draw�֐����ōU���p�̃A�j���[�V�������I�������v���C���[�̏�Ԃ�ATTACK�Ɉڍs
	// �v���C���[��ATTACK�̏ꍇ
	/*
		// �v���C���[��1�}�X��ɓG�܂���㩂��Ȃ����`�F�b�N
		// �G������ꍇ�Cplayer->attack( enemy );
		// �U���Ώ�enemy�̗̑̓`�F�b�N
		// �̗͂�0�ȉ��̏ꍇ��enemy�̏�Ԃ�DEAD�QBEGIN�ɕύX
		// 㩂�����ꍇ��㩂̏�Ԃ�visible�ɕύX
		// �v���C���[�̏�Ԃ�ATTACK�QEND�Ɉڍs
	*/
	if ( player->getState() != Player::State::ATTACK ) return;

	/*
	// �v���C���[�̕���̍U���͈͂��`�F�b�N����
	// �΂߂ɍU������Ƃ��͗אڂ��Ă���u���b�N���Ȃ����`�F�b�N����
	// �͈͓��ɑ��݂���G�ɍU�����s��
	// ���b�Z�[�W�E�B���h�E�ɑΏۖ��ƃ_���[�W�𑗂�
	for ( Enemy* enemy : enemies ) {
		if ( enemy->getX() ==  )
	}
	*/

	/*
		�G�����Ȃ���Δ͈͓���㩂̃`�F�b�N���s��
	*/
	player->setState( Player::State::ATTACK_END );
}



void DungeonLayerManager::attackByEnemy() {
	if ( !( player->getState() == Player::State::ATTACK_END || player->getState() == Player::State::MOVE_END ) ) return;

	//for (  )
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