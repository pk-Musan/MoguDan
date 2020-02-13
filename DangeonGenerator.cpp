#include "DangeonGenerator.h"
#include "DxLib.h"

#include <time.h>

DangeonGenerator::DangeonGenerator( int width, int height ) : width(width), height(height), roomNum(0), layer(0) {
	//layer = new Layer2D( width, height );
}

DangeonGenerator::~DangeonGenerator() {
	delete layer;
	layer = 0;
	/*
	for ( DangeonDivision* division : divisions ) {
		delete division;
		division = 0;
	}
	*/
}

bool DangeonGenerator::checkDivisionSize( int size ) {
	// 2�������̗]�T�����邩
	if ( size < ( MIN_ROOM_SIZE + OUTER_MERGIN * 2 ) * 2 ) return true;
	return false;
}

void DangeonGenerator::generate() {
	layer = new Layer2D( width, height );

	layer->fill( 0 ); // �w��T�C�Y�ŏ���������layer��ǂŖ��߂�
	//layer->Dump();

	createDivision( 0, 0, width - 1, height - 1 ); // �ŏ��̐e���𐶐�
	roomNum += 1;

	srand( ( unsigned int )time( nullptr ) ); // ��������ɕ������邩�ǂ����̔��f�ɗ�����p����̂ŏ�����

	splitDivison( true );
}

// �w��͈͂ŋ��𐶐����Cdivisions�ɒǉ�
void DangeonGenerator::createDivision( int left, int top, int right, int bottom ) {
	DangeonDivision* division = new DangeonDivision();
	division->outer->set( left, top, right, bottom );
	divisions.push_back( division );
}


// ���𕪊����Ă����i�����Fvertical�Ő�����������n�߂邩���߂�Cfalse�Ȃ琅����������j
/*
	��������Ăł���2���ɑ΂��čċA�I��splitDivision()���s��
	�m���C�܂��͕����̍L�������ɉ����ĕ������~�߂�
*/
void DangeonGenerator::splitDivison( bool vertical ) {
	// divisions�̖�������e�ƂȂ�v�f�����o��
	DangeonDivision* parentDiv = divisions.back();//divisions[(int)divisions.size()];
	divisions.pop_back();

	//printfDx( "%d\n", parentDiv->outer->getWidth() );

	/* 
		�e�𕪊��ł���C�܂��͊m���ɂ���ĕ�������̂�����
		�����ɂ�����m����divisions�̃T�C�Y�C�܂茻�݂̕������ɉ����ĕϓ�����̂��悳�����H
		�����ł��Ȃ����divisons�ɐe��߂���return
	*/
	// ��������(vertical)�ɉ����ĕ����\���`�F�b�N
	if ( vertical ) {
		if ( checkDivisionSize( parentDiv->outer->getHeight() ) ) {
			divisions.push_back( parentDiv );
			return;
		}
	} else {
		if ( checkDivisionSize( parentDiv->outer->getWidth() ) ) {
			divisions.push_back( parentDiv );
			return;
		}
	}

	// ������2�����ȏ゠��C�m���I�ȏ����𖞂����Ȃ��ꍇ����ȏ㕪�����Ȃ�
	if ( roomNum >= MIN_ROOM_NUM && ( rand() % 100 + 1 ) <= ( int )( ( float )roomNum / MAX_ROOM_NUM ) * 100 ) {
		divisions.push_back( parentDiv );
		return;
	}

	/*
		�������\�ł����childDiv_a, childDiv_b�𐶐�
		childDiv_a��divisions�ɉ����Ă���splitDivision���Ăяo��
		���̌�CchildDiv_b��divisions�ɉ�����splitDivision���Ăяo��

		�������邱�Ƃ�childDiv_a��e�Ƃ��Ă���ɕ������Ă����������I����Ă���
		childDiv_b��e�Ƃ��ĕ������鏈���ɓ��邱�Ƃ��ł���
	*/
	/* 
		���������ۂɍŒ���̕����̍L��(MIN_ROOM_SIZE)�ƒʘH��(OUTER_MERGIN)�͊m�ۂ��Ă����������߁C
		�����_p�����߂邽�߂ɗp����a, b�͏�L��2�̒l�����炩���ߍl�����Ă���
	*/
	int a, b;
	if ( vertical ) {
		a = parentDiv->outer->top + ( MIN_ROOM_SIZE + OUTER_MERGIN );
		b = parentDiv->outer->bottom - ( MIN_ROOM_SIZE + OUTER_MERGIN );
	} else {
		a = parentDiv->outer->left + ( MIN_ROOM_SIZE + OUTER_MERGIN );
		b = parentDiv->outer->right - ( MIN_ROOM_SIZE + OUTER_MERGIN );
	}
	int ab = b - a; // a, b�Ԃ̋���
	int p = a + rand() % ( ab + 1 );

	/* 
		�q�̋��𐶐�
		���������ɉ����Đe�̋����k�߂�
	*/
	DangeonDivision* childDiv = new DangeonDivision();
	if ( vertical ) {
		childDiv->outer->set( parentDiv->outer->left, p, parentDiv->outer->right, parentDiv->outer->bottom );
		parentDiv->outer->bottom = p;
	} else {
		childDiv->outer->set( p, parentDiv->outer->top, parentDiv->outer->right, parentDiv->outer->bottom );
		parentDiv->outer->right = p;
	}
	roomNum += 1;

	divisions.push_back( parentDiv );
	splitDivison( !vertical );

	divisions.push_back( childDiv );
	splitDivison( !vertical );
}

/*
	�e��悲�Ƃɕ����𐶐�
	1. �����̑傫���������_���Ɍ��߂�(OUTER_MERGIN���l��)
	2. �����̑傫�����l�����ċ����ł̔z�u�ꏊ�������_���Ɍ���
	3. �m�肵�������͈̔͂�ʘH�Ŗ��߂�
*/
void DangeonGenerator::createRoom() {

}