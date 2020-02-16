#include "DangeonGenerator.h"
#include "DxLib.h"

#include <time.h>
#include <vector>

DangeonGenerator::DangeonGenerator( int width, int height ) : width(width), height(height), roomNum(0), layer(0) {
	//layer = new Layer2D( width, height );
}

DangeonGenerator::~DangeonGenerator() {
	//delete layer;
	//layer = 0;
	/*
	for ( DangeonDivision* division : divisions ) {
		delete division;
		division = 0;
	}
	*/
}

bool DangeonGenerator::checkDivisionSize( int size ) {
	// 2�������̗]�T�����邩
	if ( size < ( MIN_ROOM_SIZE + OUTER_MERGIN ) * 2 + OUTER_MERGIN / 2 * 3 ) return true;
	return false;
}

void DangeonGenerator::generate() {
	//printfDx( "width = %d\nheight = %d\n", width, height );
	layer.createLayer( width, height );

	layer.fill( 1 ); // �w��T�C�Y�ŏ���������layer��ǂŖ��߂�
	//layer->Dump();

	divisions.clear();
	roomNum = 0;

	createDivision( 1, 1, width - 2, height - 2 ); // �ŏ��̐e���𐶐�
	roomNum += 1;

	srand( ( unsigned int )time( nullptr ) ); // ��������ɕ������邩�ǂ����̔��f�ɗ�����p����̂ŏ�����

	splitDivison( true );

	createRoom();

	createRoute();

	layer.Dump();
	printfDx( "room = %d\n", roomNum );
}

// �w��͈͂ŋ��𐶐����Cdivisions�ɒǉ�
void DangeonGenerator::createDivision( int left, int top, int right, int bottom ) {
	DangeonDivision division;// = new DangeonDivision();
	division.outer.set( left, top, right, bottom );
	divisions.push_back( division );
}


// ���𕪊����Ă����i�����Fvertical�Ő�����������n�߂邩���߂�Cfalse�Ȃ琅����������j
/*
	��������Ăł���2���ɑ΂��čċA�I��splitDivision()���s��
	�m���C�܂��͕����̍L�������ɉ����ĕ������~�߂�
*/
void DangeonGenerator::splitDivison( bool vertical ) {
	// divisions�̖�������e�ƂȂ�v�f�����o��
	DangeonDivision parentDiv = divisions.back();//divisions[(int)divisions.size()];
	divisions.pop_back();

	//printfDx( "%d\n", parentDiv->outer->getWidth() );

	/* 
		�e�𕪊��ł���C�܂��͊m���ɂ���ĕ�������̂�����
		�����ɂ�����m����divisions�̃T�C�Y�C�܂茻�݂̕������ɉ����ĕϓ�����̂��悳�����H
		�����ł��Ȃ����divisons�ɐe��߂���return
	*/
	// ��������(vertical)�ɉ����ĕ����\���`�F�b�N
	if ( vertical ) {
		if ( checkDivisionSize( parentDiv.outer.getHeight() ) ) {
			divisions.push_back( parentDiv );
			return;
		}
	} else {
		if ( checkDivisionSize( parentDiv.outer.getWidth() ) ) {
			divisions.push_back( parentDiv );
			return;
		}
	}

	// ������2�����ȏ゠��C�m���I�ȏ����𖞂����Ȃ��ꍇ����ȏ㕪�����Ȃ�
	int per = rand() % 100 + 1;
	int room_per = ( int )( ( float )roomNum / MAX_ROOM_NUM * 100 );
	//printfDx( "per = %d, room_per = %d\n", per, room_per );
	if ( roomNum >= MIN_ROOM_NUM && per <= room_per ) {
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
		��OUTER_MERGIN��3/2�������Ă���̂́C�אڂ��镔�����m�̌��Ԃ�3�u���b�N���ŏ\���Ȃ���
		�i2�u���b�N�������Ȃ��ƒʘH�����̍ۂɕ������狫�E���܂�1�u���b�N���ł��ǂ蒅���Ă��܂��C���E����ɉ����ĒʘH��L�΂��ۂ�
		���������������Ă��܂�����B4�u���b�N�����ƍł��߂������ł����B����̂�4�u���b�N���������Ă��܂��̂ŉ���������j

		���L�̂悤�ȕ��𕪊�����Ƃ���6��e�Ǝq�̋��E���Ƃ���
		��������΍����̋��ŕ��������Ƃ���(0, 1)���}�[�W���C(2, 4)�𕔉��C(5, 6)���}�[�W���Ƃ��邱�Ƃ��ł���
		�E���Ȃ�(6, 7)���}�[�W���C(8, 10)�𕔉��C(11, 12)���}�[�W��
		0 1 2 3 4 5 6 7 8 9 10 11 12
		            6
	*/
	int a, b;
	if ( vertical ) {
		a = parentDiv.outer.top + ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
		b = parentDiv.outer.bottom - ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
	} else {
		a = parentDiv.outer.left + ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
		b = parentDiv.outer.right - ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
	}
	int ab = b - a; // a, b�Ԃ̋���
	int p = a + rand() % ( ab + 1 ); // �����_

	/* 
		�q�̋��𐶐�
		���������ɉ����Đe�̋����k�߂�
	*/
	DangeonDivision childDiv;// = new DangeonDivision();
	if ( vertical ) {
		childDiv.outer.set( parentDiv.outer.left, p, parentDiv.outer.right, parentDiv.outer.bottom );
		parentDiv.outer.bottom = p;
	} else {
		childDiv.outer.set( p, parentDiv.outer.top, parentDiv.outer.right, parentDiv.outer.bottom );
		parentDiv.outer.right = p;
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
	for ( DangeonDivision &div : divisions ) {
		int max_room_width = div.outer.getWidth() - OUTER_MERGIN * 2; // �����̕��̍ő�l
		int max_room_height = div.outer.getHeight() - OUTER_MERGIN * 2; // �����̍����̍ő�l

		int room_width = rand() % ( max_room_width - MIN_ROOM_SIZE + 1 ) + MIN_ROOM_SIZE; // �����̕�
		int room_height = rand() % ( max_room_height - MIN_ROOM_SIZE + 1 ) + MIN_ROOM_SIZE; // �����̍���

		/*
			�e�Ǝq��6�����E���Ƃ��ĉ��L�̂悤�ɕ�������Ă������C
			�����̋��ł�(0, 1)���}�[�W���C(2, 4)�𕔉��C(5, 6)���}�[�W���Ƃ������̂�
			�ȉ��̂悤�Ɋ�_(room_x, room_y)�����߂�
			0 1 2 3 4 5 6 7 8 9 10 11 12
			            6
		*/
		int room_x = rand() % ( div.outer.getWidth() - OUTER_MERGIN *2 - room_width + 1 ) + OUTER_MERGIN; // ������x���W�i����j
		int room_y = rand() % ( div.outer.getHeight() - OUTER_MERGIN *2 - room_height + 1 ) + OUTER_MERGIN; // ������y���W�i����j

		int left = div.outer.left + room_x;
		int top = div.outer.top + room_y;
		int right = left + room_width - 1;
		int bottom = top + room_height - 1;
		// 0 1 2 3
		// 0 1 2 3 4 5 6 7 8
		// 1 2 3 4 5 6 7 8 9
		//   2 3 4 5
		div.inner.set( left, top, right, bottom );

		//layer.fillRectLTRB( div.outer.left, div.outer.top, div.outer.right, div.outer.bottom, 2 );
		//layer.fillRectLTRB( div.outer.left+1, div.outer.top+1, div.outer.right-1, div.outer.bottom-1, 1 );
		fillRoom( div.inner );
	}
}

void DangeonGenerator::fillRoom( DangeonDivision::DangeonRectangle inner ) {
	layer.fillRectLTRB( inner.left, inner.top, inner.right, inner.bottom, 0 );
}

void DangeonGenerator::createRoute() {
	// ��������O���̋��܂ŒʘH�����΂�
	for ( DangeonDivision &div : divisions ) {
		// ��������ʘH���o���ꏊ�����߂�i4�������j
		int inner_left = div.inner.left;
		int inner_top = div.inner.top;
		int inner_right = div.inner.right;
		int inner_bottom = div.inner.bottom;

		int outer_left = div.outer.left;
		int outer_top = div.outer.top;
		int outer_right = div.outer.right;
		int outer_bottom = div.outer.bottom;

		int left_y = rand() % ( inner_bottom - inner_top + 1 ) + inner_top; // �����̍�������o��ʘH��y���W
		int top_x = rand() % ( inner_right - inner_left + 1 ) + inner_left; // �����̏㑤����o��ʘH��x���W
		int right_y = rand() % ( inner_bottom - inner_top + 1 ) + inner_top; // �����̉E������o��ʘH��y���W
		int bottom_x = rand() % ( inner_right - inner_left + 1 ) + inner_left; // �����̉�������o��ʘH��x���W

		layer.fillRectLTRB( outer_left, left_y, inner_left - 1, left_y, 0 );
		layer.fillRectLTRB( top_x, outer_top, top_x, inner_top - 1, 0 );
		layer.fillRectLTRB( inner_right + 1, right_y, outer_right, right_y, 0 );
		layer.fillRectLTRB( bottom_x, inner_bottom + 1, bottom_x, outer_bottom, 0 );
	}

	// �e�������牄�΂��ꂽ�ʘH���Ȃ�
	for ( DangeonDivision& div : divisions ) {
		int y, x;
		std::vector<int> route_knots;

		// ���̍���
		x = div.outer.left;
		for ( y = div.outer.top; y <= div.outer.bottom; y++ ) {
			if ( layer( y, x ) == 0 ) route_knots.push_back( y );
		}
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( x, route_knots.front(), x, route_knots.back(), 0 );
		else if ( route_knots.size() == 1 ) {
			if ( layer( route_knots.front(), x - 1 ) != 0 ) layer.fillRectLTRB( x, route_knots.front(), div.inner.left - 1, route_knots.front(), 1 );
		}
		route_knots.clear();

		
		// ���̏㑤
		y = div.outer.top;
		for ( x = div.outer.left; x <= div.outer.right; x++ ) {
			if ( layer( y, x ) == 0 ) route_knots.push_back( x );
		}
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( route_knots.front(), y, route_knots.back(), y, 0 );
		else if ( route_knots.size() == 1 ) {
			if ( layer( y - 1, route_knots.front() ) != 0 ) layer.fillRectLTRB( route_knots.front(), y, route_knots.front(), div.inner.top - 1, 1 );
		}
		route_knots.clear();

		// ���̉E��
		x = div.outer.right;
		for ( y = div.outer.top; y <= div.outer.bottom; y++ ) {
			if ( layer( y, x ) == 0 ) route_knots.push_back( y );
		}
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( x, route_knots.front(), x, route_knots.back(), 0 );
		else if ( route_knots.size() == 1 ) {
			if ( layer( route_knots.front(), x + 1 ) != 0 ) layer.fillRectLTRB( div.inner.right + 1, route_knots.front(), x, route_knots.front(), 1 );
		}
		route_knots.clear();

		// ���̉���
		y = div.outer.bottom;
		for ( x = div.outer.left; x <= div.outer.right; x++ ) {
			if ( layer( y, x ) == 0 ) route_knots.push_back( x );
		}
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( route_knots.front(), y, route_knots.back(), y, 0 );
		else if ( route_knots.size() == 1 ) {
			if ( layer( y + 1, route_knots.front() ) != 0 ) layer.fillRectLTRB( route_knots.front(), div.inner.bottom + 1, route_knots.front(), y, 1 );
		}
		route_knots.clear();
	}
}