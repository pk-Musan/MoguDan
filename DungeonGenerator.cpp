#include "DungeonGenerator.h"
#include "DxLib.h"

#include <time.h>
#include <vector>
#include <algorithm>

DungeonGenerator::DungeonGenerator( int width, int height ) : width(width), height(height), roomNum(0), layer(0) {
	//layer = new Layer2D( width, height );
}

DungeonGenerator::~DungeonGenerator() {
	//delete layer;
	//layer = 0;
	/*
	for ( DangeonDivision* division : divisions ) {
		delete division;
		division = 0;
	}
	*/
}

bool DungeonGenerator::checkDivisionSize( int size ) {
	// 2�������̗]�T�����邩
	if ( size < ( MIN_ROOM_SIZE + OUTER_MERGIN ) * 2 + OUTER_MERGIN / 2 * 3 ) return true;
	return false;
}

void DungeonGenerator::generate() {
	//printfDx( "width = %d\nheight = %d\n", width, height );
	layer.createLayer( width, height );

	layer.fill( 1 ); // �w��T�C�Y�ŏ���������layer��ǂŖ��߂�
	//layer->Dump();

	divisions.clear();
	roomNum = 0;

	createDivision( 5, 5, width - 1 - 5, height - 1 - 5 ); // �ŏ��̐e���𐶐�
	roomNum += 1;

	srand( ( unsigned int )time( nullptr ) ); // ��������ɕ������邩�ǂ����̔��f�ɗ�����p����̂ŏ�����

	bool vertical = ( rand() % 2 == 0 );
	splitDivison( vertical );

	createRoom();

	//sortDivisionByArea();

	createRoute();

	layer.Dump();
	printfDx( "room = %d\n", roomNum );
	for ( DungeonDivision* div : divisions ) printfDx( "%d ", div->inner.getHeight() * div->inner.getWidth() );
}

// �w��͈͂ŋ��𐶐����Cdivisions�ɒǉ�
void DungeonGenerator::createDivision( int left, int top, int right, int bottom ) {
	DungeonDivision* division = new DungeonDivision();
	division->outer.set( left, top, right, bottom );
	divisions.push_back( division );
}


// ���𕪊����Ă����i�����Fvertical�Ő�����������n�߂邩���߂�Cfalse�Ȃ琅����������j
/*
	��������Ăł���2���ɑ΂��čċA�I��splitDivision()���s��
	�m���C�܂��͕����̍L�������ɉ����ĕ������~�߂�
*/
void DungeonGenerator::splitDivison( bool vertical ) {
	// divisions�̖�������e�ƂȂ�v�f�����o��
	DungeonDivision* parentDiv = divisions.back();//divisions[(int)divisions.size()];
	divisions.pop_back();

	//printfDx( "%d\n", parentDiv->outer->getWidth() );

	/* 
		�e�𕪊��ł���C�܂��͊m���ɂ���ĕ�������̂�����
		�����ɂ�����m����divisions�̃T�C�Y�C�܂茻�݂̕������ɉ����ĕϓ�����̂��悳�����H
		�����ł��Ȃ����divisons�ɐe��߂���return
	*/
	// ��������(vertical)�ɉ����ĕ����\���`�F�b�N
	if ( vertical ) {
		if ( checkDivisionSize( parentDiv->outer.getHeight() ) ) {
			divisions.push_back( parentDiv );
			return;
		}
	} else {
		if ( checkDivisionSize( parentDiv->outer.getWidth() ) ) {
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
		a = parentDiv->outer.top + ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
		b = parentDiv->outer.bottom - ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
	} else {
		a = parentDiv->outer.left + ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
		b = parentDiv->outer.right - ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
	}
	int ab = b - a; // a, b�Ԃ̋���
	int p = a + rand() % ( ab + 1 ); // �����_

	/* 
		�q�̋��𐶐�
		���������ɉ����Đe�̋����k�߂�
	*/
	DungeonDivision* childDiv = new DungeonDivision();
	if ( vertical ) {
		childDiv->outer.set( parentDiv->outer.left, p, parentDiv->outer.right, parentDiv->outer.bottom );
		parentDiv->outer.bottom = p;
	} else {
		childDiv->outer.set( p, parentDiv->outer.top, parentDiv->outer.right, parentDiv->outer.bottom );
		parentDiv->outer.right = p;
	}
	roomNum += 1;

	// �e���Ǝq���̂ǂ�����ɕ������邩�itrue�Ȃ�e����j
	bool splitParent = ( rand() % 2 == 0 );
	if ( splitParent ) {
		divisions.push_back( parentDiv );
		splitDivison( !vertical );

		divisions.push_back( childDiv );
		splitDivison( !vertical );
	} else {
		divisions.push_back( childDiv );
		splitDivison( !vertical );

		divisions.push_back( parentDiv );
		splitDivison( !vertical );
	}
}


/*
	�e��悲�Ƃɕ����𐶐�
	1. �����̑傫���������_���Ɍ��߂�(OUTER_MERGIN���l��)
	2. �����̑傫�����l�����ċ����ł̔z�u�ꏊ�������_���Ɍ���
	3. �m�肵�������͈̔͂�ʘH�Ŗ��߂�
*/
void DungeonGenerator::createRoom() {
	int ratio = 60;
	for ( DungeonDivision* div : divisions ) {
		int max_room_width = div->outer.getWidth() - OUTER_MERGIN * 2; // �����̕��̍ő�l
		int max_room_height = div->outer.getHeight() - OUTER_MERGIN * 2; // �����̍����̍ő�l

		int min_room_width = max(max_room_width * ratio / 100, MIN_ROOM_SIZE);
		int min_room_height = max(max_room_height * ratio / 100, MIN_ROOM_SIZE);

		int room_width = rand() % ( max_room_width - min_room_width + 1 ) + min_room_width; // �����̕�
		int room_height = rand() % ( max_room_height - min_room_height + 1 ) + min_room_height; // �����̍���

		/*
			�e�Ǝq��6�����E���Ƃ��ĉ��L�̂悤�ɕ�������Ă������C
			�����̋��ł�(0, 1)���}�[�W���C(2, 4)�𕔉��C(5, 6)���}�[�W���Ƃ������̂�
			�ȉ��̂悤�Ɋ�_(room_x, room_y)�����߂�
			0 1 2 3 4 5 6 7 8 9 10 11 12
			            6
		*/
		int room_x = rand() % ( div->outer.getWidth() - OUTER_MERGIN *2 - room_width + 1 ) + OUTER_MERGIN; // ������x���W�i����j
		int room_y = rand() % ( div->outer.getHeight() - OUTER_MERGIN *2 - room_height + 1 ) + OUTER_MERGIN; // ������y���W�i����j

		int left = div->outer.left + room_x;
		int top = div->outer.top + room_y;
		int right = left + room_width - 1;
		int bottom = top + room_height - 1;
		// 0 1 2 3
		// 0 1 2 3 4 5 6 7 8
		// 1 2 3 4 5 6 7 8 9
		//   2 3 4 5
		div->inner.set( left, top, right, bottom );

		layer.fillRectLTRB( div->outer.left, div->outer.top, div->outer.right, div->outer.bottom, 2 );
		layer.fillRectLTRB( div->outer.left+1, div->outer.top+1, div->outer.right-1, div->outer.bottom-1, 1 );
		fillRoom( div->inner );
	}
}


/*
	�w�肳�ꂽ���𕔉��Ƃ��ď���������
*/
void DungeonGenerator::fillRoom( DungeonDivision::DungeonRectangle inner ) {
	layer.fillRectLTRB( inner.left, inner.top, inner.right, inner.bottom, 0 );
}


/*
	����ʐς̑傫�����ɕ��ѕς���
	�ʘH�����̍ۂɑ傫�����ɑ΂���ʘH���ɒ[�ɏ��Ȃ��Ȃ�̂�h������
*/
void DungeonGenerator::sortDivisionByArea() {
	//std::sort( divisions.begin(), divisions.end() );

	divisions.sort( []( const DungeonDivision* divA, const DungeonDivision* divB ) {
		return divA->inner.getWidth() * divA->inner.getHeight() > divB->inner.getWidth()* divB->inner.getHeight();
	} );
}


/*
	�������m�����ԒʘH�𐶐�����
*/
void DungeonGenerator::createRoute() {
	// ��������O���̋��܂ŒʘH�����΂�
	for ( DungeonDivision* div : divisions ) {
		// ��������ʘH���o���ꏊ�����߂�i4�������j
		int inner_left = div->inner.left;
		int inner_top = div->inner.top;
		int inner_right = div->inner.right;
		int inner_bottom = div->inner.bottom;

		int outer_left = div->outer.left;
		int outer_top = div->outer.top;
		int outer_right = div->outer.right;
		int outer_bottom = div->outer.bottom;

		int left_y = rand() % ( inner_bottom - inner_top + 1 ) + inner_top; // �����̍�������o��ʘH��y���W
		int top_x = rand() % ( inner_right - inner_left + 1 ) + inner_left; // �����̏㑤����o��ʘH��x���W
		int right_y = rand() % ( inner_bottom - inner_top + 1 ) + inner_top; // �����̉E������o��ʘH��y���W
		int bottom_x = rand() % ( inner_right - inner_left + 1 ) + inner_left; // �����̉�������o��ʘH��x���W

		layer.fillRectLTRB( outer_left, left_y, inner_left - 1, left_y, 0 );
		layer.fillRectLTRB( top_x, outer_top, top_x, inner_top - 1, 0 );
		layer.fillRectLTRB( inner_right + 1, right_y, outer_right, right_y, 0 );
		layer.fillRectLTRB( bottom_x, inner_bottom + 1, bottom_x, outer_bottom, 0 );
	}

	//sortDivisionByArea();

	connectRoute();
}

/*
	�ʘH���m������
*/
void DungeonGenerator::connectRoute() {
	// �e�������牄�΂��ꂽ�ʘH���Ȃ�
	for ( DungeonDivision* div : divisions ) {
		int y, x; // �������牄�΂��ꂽ�ʘH���O���̋��̂ǂ��ɂ��邩
		std::vector<int> route_knots; // ��������̈�ӂɑ��݂���ʘH�̐�

		/*
			�������ɉ����ĒʘH���m���Ȃ��͈͂�ύX����
			4�����ȉ��̏ꍇ�C�e���ł͎��g�̋��(outer)���͈̔͂����`�F�b�N���Ȃ�
		*/
		int y_min, y_max, x_min, x_max;
		if ( divisions.size() <= 4 ) {
			y_min = div->outer.top;
			y_max = div->outer.bottom + 1;
			x_min = div->outer.left;
			x_max = div->outer.right + 1;
		} else {
			y_min = 0;
			y_max = height;
			x_min = 0;
			x_max = width;
		}

		/*
		##################
		####���̍���####
		##################
		*/
		x = div->outer.left;
		// �����̍����ȓ��͈̔͂Őڑ��_��T���i����悩��o�Ă���o�H�̓˂�������܂ށj
		for ( y = div->inner.top; y <= div->inner.bottom; y++ ) {
			if ( layer( y, x ) == 0 ) {
				route_knots.push_back( y );
			}
		}

		// �����̍����ȓ��͈̔͂ɐڑ��_���Ȃ������ꍇ�i�P�����Ȃ��Ă��܂������ɑ��̕����ƂȂ����Ă���ꍇ�͏����j
		if ( route_knots.size() == 1 && layer( route_knots.front(), x - 1 ) != 0 ) {
			bool vertical = true;
			bool searchUp = ( rand() % 2 == 0 );

			if ( searchUp ) {
				searchKnot( div->inner.top - 1, y_min, x, vertical, route_knots );
				searchKnot( div->inner.bottom + 1, y_max, x, vertical, route_knots );
			} else {
				searchKnot( div->inner.bottom + 1, y_max, x, vertical, route_knots );
				searchKnot( div->inner.top - 1, y_min, x, vertical, route_knots );
			}
		}

		// �ڑ��_��2�ȏ゠��΂�����ʘH�Ƃ��Č���
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( x, route_knots.front(), x, route_knots.back(), 0 );
		// �ڑ��_��1�����Ȃ��Ƃ��͕����܂ł̒ʘH�������i���͂ɋ�Ԃ����݂���ꍇ�������j
		else if ( route_knots.size() == 1 ) {
			for ( ; x < div->inner.left; x++ ) {
				int l = layer( route_knots.front(), x - 1 );
				int u = layer( route_knots.front() - 1, x );
				int d = layer( route_knots.front() + 1, x );
				if ( l != 0 && u != 0 && d != 0 ) layer.fillRectLTRB( x, route_knots.front(), x, route_knots.front(), 1 );
				else break;
			}
		}
		route_knots.clear();


		/*
		##################
		####���̏㑤####
		##################
		*/
		y = div->outer.top;
		// �����̕��ȓ��͈̔͂Őڑ��_��T���i����悩��o�Ă���o�H�̓˂�������܂ށj
		for ( x = div->inner.left; x <= div->inner.right; x++ ) {
			if ( layer( y, x ) == 0 ) {
				route_knots.push_back( x );
			}
		}

		// �����̕��ȓ��͈̔͂ɐڑ��_���Ȃ������ꍇ�i�P�����Ȃ��Ă��܂������ɑ��̕����ƂȂ����Ă���ꍇ�͏����j
		if ( route_knots.size() == 1 && layer( y - 1, route_knots.front() ) != 0 ) {
			bool vertical = false;
			bool searchLeft = ( rand() % 2 == 0 );

			if ( searchLeft ) {
				searchKnot( div->inner.left - 1, x_min, y, vertical, route_knots );
				searchKnot( div->inner.right + 1, x_max, y, vertical, route_knots );
			} else {
				searchKnot( div->inner.right + 1, x_max, y, vertical, route_knots );
				searchKnot( div->inner.left - 1, x_min, y, vertical, route_knots );
			}
		}

		// �ڑ��_��2�ȏ゠��΂�����ʘH�Ƃ��Č���
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( route_knots.front(), y, route_knots.back(), y, 0 );
		// �ڑ��_��1�����Ȃ��Ƃ��͕����܂ł̒ʘH�������i���͂ɋ�Ԃ����݂���ꍇ�������j
		else if ( route_knots.size() == 1 ) {
			for ( ; y < div->inner.top; y++ ) {
				int l = layer( y, route_knots.front() - 1 );
				int u = layer( y - 1, route_knots.front() );
				int r = layer( y, route_knots.front() + 1 );
				if ( l != 0 && u != 0 && r != 0 ) layer.fillRectLTRB( route_knots.front(), y, route_knots.front(), y, 1 );
				else break;
			}
		}
		route_knots.clear();


		/*
		##################
		####���̉E��####
		##################
		*/
		x = div->outer.right;
		// �����̍����ȓ��͈̔͂Őڑ��_��T���i����悩��o�Ă���o�H�̓˂�������܂ށj
		for ( y = div->inner.top; y <= div->inner.bottom; y++ ) {
			if ( layer( y, x ) == 0 ) {
				route_knots.push_back( y );
			}
		}

		// �����̍����ȓ��͈̔͂ɐڑ��_���Ȃ������ꍇ�i�P�����Ȃ��Ă��܂������ɑ��̕����ƂȂ����Ă���ꍇ�͏����j
		if ( route_knots.size() == 1 && layer( route_knots.front(), x + 1 ) != 0 ) {
			bool vertical = true;
			bool searchUp = ( rand() % 2 == 0 );

			if ( searchUp ) {
				searchKnot( div->inner.top - 1, y_min, x, vertical, route_knots );
				searchKnot( div->inner.bottom + 1, y_max, x, vertical, route_knots );
			} else {
				searchKnot( div->inner.bottom + 1, y_max, x, vertical, route_knots );
				searchKnot( div->inner.top - 1, y_min, x, vertical, route_knots );
			}
		}

		// �ڑ��_��2�ȏ゠��΂�����ʘH�Ƃ��Č���
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( x, route_knots.front(), x, route_knots.back(), 0 );
		// �ڑ��_��1�����Ȃ��Ƃ��͕����܂ł̒ʘH�������i���͂ɋ�Ԃ����݂���ꍇ�������j
		else if ( route_knots.size() == 1 ) {
			for ( ; x > div->inner.right; x-- ) {
				int u = layer( route_knots.front() - 1, x );
				int r = layer( route_knots.front(), x + 1 );
				int d = layer( route_knots.front() + 1, x );
				if ( u != 0 && r != 0 && d != 0 ) layer.fillRectLTRB( x, route_knots.front(), x, route_knots.front(), 1 );
				else break;
			}
		}
		route_knots.clear();

		/*
		##################
		####���̉���####
		##################
		*/
		y = div->outer.bottom;
		// �����̕��ȓ��͈̔͂Őڑ��_��T���i����悩��o�Ă���o�H�̓˂�������܂ށj
		for ( x = div->inner.left; x <= div->inner.right; x++ ) {
			if ( layer( y, x ) == 0 ) {
				route_knots.push_back( x );
			}
		}

		// �����̕��ȓ��͈̔͂ɐڑ��_���Ȃ������ꍇ�i�P�����Ȃ��Ă��܂������ɑ��̕����ƂȂ����Ă���ꍇ�͏����j
		if ( route_knots.size() == 1 && layer( y + 1, route_knots.front() ) != 0 ) {
			bool vertical = false;
			bool searchLeft = ( rand() % 2 == 0 );

			if ( searchLeft ) {
				searchKnot( div->inner.left - 1, x_min, y, vertical, route_knots );
				searchKnot( div->inner.right + 1, x_max, y, vertical, route_knots );
			} else {
				searchKnot( div->inner.right + 1, x_max, y, vertical, route_knots );
				searchKnot( div->inner.left - 1, x_min, y, vertical, route_knots );
			}
		}

		// �ڑ��_��2�ȏ゠��΂�����ʘH�Ƃ��Č���
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( route_knots.front(), y, route_knots.back(), y, 0 );
		// �ڑ��_��1�����Ȃ��Ƃ��͕����܂ł̒ʘH�������i���͂ɋ�Ԃ����݂���ꍇ�������j
		else if ( route_knots.size() == 1 ) {
			for ( ; y > div->inner.bottom; y-- ) {
				int l = layer( y, route_knots.front() - 1 );
				int r = layer( y, route_knots.front() + 1 );
				int d = layer( y + 1, route_knots.front() );
				if ( l != 0 && r != 0 && d != 0 ) layer.fillRectLTRB( route_knots.front(), y, route_knots.front(), y, 1 );
			}
		}
		route_knots.clear();
	}
}


void DungeonGenerator::searchKnot( int from, int to, int fixedPoint, bool vertical, std::vector<int>& knots ) {
	if ( knots.size() > 1 ) return;

	// �c�����̐ڑ��_�T�[�`
	if ( vertical ) {
		int x = fixedPoint;
		int y;

		if ( from <= to ) {
			for ( y = from; y < to; y++ ) {
				// ��Ԃ�3�ȏ㑱���Ă���ꍇ�͒ʘH�����΂��ƕ������ђʂ��Ă��܂��̂�break
				if ( y < height - 2 ) {
					if ( layer( y, x ) == 0 && layer( y + 1, x ) == 0 && layer( y + 2, x ) == 0 ) break;
					if ( layer( y, x - 1 ) == 0 && layer( y + 1, x - 1 ) == 0 && layer( y + 2, x - 1 ) == 0 ) break;
					if ( layer( y, x + 1 ) == 0 && layer( y + 1, x + 1 ) == 0 && layer( y + 2, x + 1 ) == 0 ) break;
				}
				if ( layer( y, x ) == 0 ) {
					knots.push_back( y );
					break;
				}
			}
		} else {
			for ( y = from; y >= to; y-- ) {
				// ��Ԃ�3�ȏ㑱���Ă���ꍇ�͒ʘH�����΂��ƕ������ђʂ��Ă��܂��̂�break
				if ( y >= 2 ) {
					if ( layer( y, x ) == 0 && layer( y - 1, x ) == 0 && layer( y - 2, x ) == 0 ) break;
					if ( layer( y, x - 1 ) == 0 && layer( y - 1, x - 1 ) == 0 && layer( y - 2, x - 1 ) == 0 ) break;
					if ( layer( y, x + 1 ) == 0 && layer( y - 1, x + 1 ) == 0 && layer( y - 2, x + 1 ) == 0 ) break;
				}
				if ( layer( y, x ) == 0 ) {
					knots.insert( knots.begin(), y );
					break;
				}
			}
		}
	} else { // �������̃T�[�`
		int y = fixedPoint;
		int x;

		if ( from <= to ) {
			for ( x = from; x < to; x++ ) {
				// ��Ԃ�3�ȏ㑱���Ă���ꍇ�͒ʘH�����΂��ƕ������ђʂ��Ă��܂��̂�break
				if ( x < width - 2 ) {
					if ( layer( y, x ) == 0 && layer( y, x + 1 ) == 0 && layer( y, x + 2 ) == 0 ) break;
					if ( layer( y - 1, x ) == 0 && layer( y - 1, x + 1 ) == 0 && layer( y - 1, x + 2 ) == 0 ) break;
					if ( layer( y + 1, x ) == 0 && layer( y + 1, x + 1 ) == 0 && layer( y + 1, x + 2 ) == 0 ) break;
				}
				if ( layer( y, x ) == 0 ) {
					knots.push_back( x );
					break;
				}
			}
		} else {
			for ( x = from; x >= to; x-- ) {
				// ��Ԃ�3�ȏ㑱���Ă���ꍇ�͒ʘH�����΂��ƕ������ђʂ��Ă��܂��̂�break
				if ( x >= 2 ) {
					if ( layer( y, x ) == 0 && layer( y, x - 1 ) == 0 && layer( y, x - 2 ) == 0 ) break;
					if ( layer( y - 1, x ) == 0 && layer( y - 1, x - 1 ) == 0 && layer( y - 1, x - 2 ) == 0 ) break;
					if ( layer( y + 1, x ) == 0 && layer( y + 1, x - 1 ) == 0 && layer( y + 1, x - 2 ) == 0 ) break;
				}
				if ( layer( y, x ) == 0 ) {
					knots.insert( knots.begin(), x );
					break;
				}
			}
		}
	}
}