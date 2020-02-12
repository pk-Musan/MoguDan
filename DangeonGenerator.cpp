#include "DangeonGenerator.h"
#include "DxLib.h"

DangeonGenerator::DangeonGenerator( int width, int height ) : width(width), height(height), layer(0) {
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

bool DangeonGenerator::checkDivisionHeight( int height ) {
	//if ( height <  )
	return true;
}

void DangeonGenerator::generate() {
	layer = new Layer2D( width, height );

	layer->fill( 0 );
	//layer->Dump();

	createDivision( 0, 0, width - 1, height - 1 );

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

	/*
		�������\�ł����childDiv_a, childDiv_b�𐶐�
		childDiv_a��divisions�ɉ����Ă���splitDivision���Ăяo��
		���̌�CchildDiv_b��divisions�ɉ�����splitDivision���Ăяo��

		�������邱�Ƃ�childDiv_a��e�Ƃ��Ă���ɕ������Ă����������I����Ă���
		childDiv_b��e�Ƃ��ĕ������鏈���ɓ��邱�Ƃ��ł���
	*/
}

