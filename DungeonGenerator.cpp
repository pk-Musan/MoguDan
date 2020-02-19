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
	// 2部屋分の余裕があるか
	if ( size < ( MIN_ROOM_SIZE + OUTER_MERGIN ) * 2 + OUTER_MERGIN / 2 * 3 ) return true;
	return false;
}

void DungeonGenerator::generate() {
	//printfDx( "width = %d\nheight = %d\n", width, height );
	layer.createLayer( width, height );

	layer.fill( 1 ); // 指定サイズで初期化したlayerを壁で埋める
	//layer->Dump();

	divisions.clear();
	roomNum = 0;

	createDivision( 5, 5, width - 1 - 5, height - 1 - 5 ); // 最初の親区画を生成
	roomNum += 1;

	srand( ( unsigned int )time( nullptr ) ); // 区画をさらに分割するかどうかの判断に乱数を用いるので初期化

	bool vertical = ( rand() % 2 == 0 );
	splitDivison( vertical );

	createRoom();

	//sortDivisionByArea();

	createRoute();

	layer.Dump();
	printfDx( "room = %d\n", roomNum );
	for ( DungeonDivision* div : divisions ) printfDx( "%d ", div->inner.getHeight() * div->inner.getWidth() );
}

// 指定範囲で区画を生成し，divisionsに追加
void DungeonGenerator::createDivision( int left, int top, int right, int bottom ) {
	DungeonDivision* division = new DungeonDivision();
	division->outer.set( left, top, right, bottom );
	divisions.push_back( division );
}


// 区画を分割していく（引数：verticalで垂直分割から始めるか決める，falseなら水平分割から）
/*
	分割されてできた2区画に対して再帰的にsplitDivision()を行う
	確率，または部屋の広さ制限に応じて分割を止める
*/
void DungeonGenerator::splitDivison( bool vertical ) {
	// divisionsの末尾から親となる要素を取り出す
	DungeonDivision* parentDiv = divisions.back();//divisions[(int)divisions.size()];
	divisions.pop_back();

	//printfDx( "%d\n", parentDiv->outer->getWidth() );

	/* 
		親を分割できる，または確立によって分割するのか決定
		ここにおける確率はdivisionsのサイズ，つまり現在の部屋数に応じて変動するのがよさそう？
		分割できなければdivisonsに親を戻してreturn
	*/
	// 分割方向(vertical)に応じて分割可能かチェック
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

	// 部屋が2部屋以上あり，確率的な条件を満たさない場合これ以上分割しない
	int per = rand() % 100 + 1;
	int room_per = ( int )( ( float )roomNum / MAX_ROOM_NUM * 100 );
	//printfDx( "per = %d, room_per = %d\n", per, room_per );
	if ( roomNum >= MIN_ROOM_NUM && per <= room_per ) {
		divisions.push_back( parentDiv );
		return;
	}

	/*
		分割が可能であればchildDiv_a, childDiv_bを生成
		childDiv_aをdivisionsに加えてからsplitDivisionを呼び出す
		その後，childDiv_bをdivisionsに加えてsplitDivisionを呼び出す

		こうすることでchildDiv_aを親としてさらに分割していく処理が終わってから
		childDiv_bを親として分割する処理に入ることができる
	*/
	/* 
		分割した際に最低限の部屋の広さ(MIN_ROOM_SIZE)と通路幅(OUTER_MERGIN)は確保しておきたいため，
		分割点pを求めるために用いるa, bは上記の2つの値をあらかじめ考慮しておく
		※OUTER_MERGINに3/2をかけているのは，隣接する部屋同士の隙間は3ブロック分で十分なため
		（2ブロック分しかないと通路生成の際に部屋から境界線まで1ブロック分でたどり着いてしまい，境界線上に沿って通路を伸ばす際に
		部屋をえぐり取ってしまうから。4ブロック分だと最も近い部屋でも到達するのに4ブロック分かかってしまうので遠く感じる）

		下記のような幅を分割するときは6を親と子の境界線とする
		こうすれば左側の区画で部屋を作るときは(0, 1)をマージン，(2, 4)を部屋，(5, 6)をマージンとすることができる
		右側なら(6, 7)をマージン，(8, 10)を部屋，(11, 12)をマージン
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
	int ab = b - a; // a, b間の距離
	int p = a + rand() % ( ab + 1 ); // 分割点

	/* 
		子の区画を生成
		分割方向に応じて親の区画を縮める
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

	// 親区画と子区画のどちらを先に分割するか（trueなら親から）
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
	各区画ごとに部屋を生成
	1. 部屋の大きさをランダムに決める(OUTER_MERGINを考慮)
	2. 部屋の大きさを考慮して区画内での配置場所をランダムに決定
	3. 確定した部屋の範囲を通路で埋める
*/
void DungeonGenerator::createRoom() {
	int ratio = 60;
	for ( DungeonDivision* div : divisions ) {
		int max_room_width = div->outer.getWidth() - OUTER_MERGIN * 2; // 部屋の幅の最大値
		int max_room_height = div->outer.getHeight() - OUTER_MERGIN * 2; // 部屋の高さの最大値

		int min_room_width = max(max_room_width * ratio / 100, MIN_ROOM_SIZE);
		int min_room_height = max(max_room_height * ratio / 100, MIN_ROOM_SIZE);

		int room_width = rand() % ( max_room_width - min_room_width + 1 ) + min_room_width; // 部屋の幅
		int room_height = rand() % ( max_room_height - min_room_height + 1 ) + min_room_height; // 部屋の高さ

		/*
			親と子が6を境界線として下記のように分割されていた時，
			左側の区画では(0, 1)をマージン，(2, 4)を部屋，(5, 6)をマージンとしたいので
			以下のように基準点(room_x, room_y)を求める
			0 1 2 3 4 5 6 7 8 9 10 11 12
			            6
		*/
		int room_x = rand() % ( div->outer.getWidth() - OUTER_MERGIN *2 - room_width + 1 ) + OUTER_MERGIN; // 部屋のx座標（左上）
		int room_y = rand() % ( div->outer.getHeight() - OUTER_MERGIN *2 - room_height + 1 ) + OUTER_MERGIN; // 部屋のy座標（左上）

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
	指定された区画を部屋として書き換える
*/
void DungeonGenerator::fillRoom( DungeonDivision::DungeonRectangle inner ) {
	layer.fillRectLTRB( inner.left, inner.top, inner.right, inner.bottom, 0 );
}


/*
	区画を面積の大きい順に並び変える
	通路生成の際に大きい区画に対する通路が極端に少なくなるのを防ぐため
*/
void DungeonGenerator::sortDivisionByArea() {
	//std::sort( divisions.begin(), divisions.end() );

	divisions.sort( []( const DungeonDivision* divA, const DungeonDivision* divB ) {
		return divA->inner.getWidth() * divA->inner.getHeight() > divB->inner.getWidth()* divB->inner.getHeight();
	} );
}


/*
	部屋同士を結ぶ通路を生成する
*/
void DungeonGenerator::createRoute() {
	// 部屋から外側の区画まで通路を延ばす
	for ( DungeonDivision* div : divisions ) {
		// 部屋から通路を出す場所を決める（4方向分）
		int inner_left = div->inner.left;
		int inner_top = div->inner.top;
		int inner_right = div->inner.right;
		int inner_bottom = div->inner.bottom;

		int outer_left = div->outer.left;
		int outer_top = div->outer.top;
		int outer_right = div->outer.right;
		int outer_bottom = div->outer.bottom;

		int left_y = rand() % ( inner_bottom - inner_top + 1 ) + inner_top; // 部屋の左側から出る通路のy座標
		int top_x = rand() % ( inner_right - inner_left + 1 ) + inner_left; // 部屋の上側から出る通路のx座標
		int right_y = rand() % ( inner_bottom - inner_top + 1 ) + inner_top; // 部屋の右側から出る通路のy座標
		int bottom_x = rand() % ( inner_right - inner_left + 1 ) + inner_left; // 部屋の下側から出る通路のx座標

		layer.fillRectLTRB( outer_left, left_y, inner_left - 1, left_y, 0 );
		layer.fillRectLTRB( top_x, outer_top, top_x, inner_top - 1, 0 );
		layer.fillRectLTRB( inner_right + 1, right_y, outer_right, right_y, 0 );
		layer.fillRectLTRB( bottom_x, inner_bottom + 1, bottom_x, outer_bottom, 0 );
	}

	//sortDivisionByArea();

	connectRoute();
}

/*
	通路同士を結ぶ
*/
void DungeonGenerator::connectRoute() {
	// 各部屋から延ばされた通路をつなぐ
	for ( DungeonDivision* div : divisions ) {
		int y, x; // 部屋から延ばされた通路が外側の区画のどこにあるか
		std::vector<int> route_knots; // 同一区画内の一辺に存在する通路の数

		/*
			部屋数に応じて通路同士をつなぐ範囲を変更する
			4部屋以下の場合，各区画では自身の区画(outer)内の範囲しかチェックしない
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
		####区画の左側####
		##################
		*/
		x = div->outer.left;
		// 部屋の高さ以内の範囲で接続点を探す（自区画から出ている経路の突き当りも含む）
		for ( y = div->inner.top; y <= div->inner.bottom; y++ ) {
			if ( layer( y, x ) == 0 ) {
				route_knots.push_back( y );
			}
		}

		// 部屋の高さ以内の範囲に接続点がなかった場合（１つしかなくてもまっすぐに他の部屋とつながっている場合は除く）
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

		// 接続点が2つ以上あればそれらを通路として結ぶ
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( x, route_knots.front(), x, route_knots.back(), 0 );
		// 接続点が1つしかないときは部屋までの通路を消す（周囲に空間が存在する場合を除く）
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
		####区画の上側####
		##################
		*/
		y = div->outer.top;
		// 部屋の幅以内の範囲で接続点を探す（自区画から出ている経路の突き当りも含む）
		for ( x = div->inner.left; x <= div->inner.right; x++ ) {
			if ( layer( y, x ) == 0 ) {
				route_knots.push_back( x );
			}
		}

		// 部屋の幅以内の範囲に接続点がなかった場合（１つしかなくてもまっすぐに他の部屋とつながっている場合は除く）
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

		// 接続点が2つ以上あればそれらを通路として結ぶ
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( route_knots.front(), y, route_knots.back(), y, 0 );
		// 接続点が1つしかないときは部屋までの通路を消す（周囲に空間が存在する場合を除く）
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
		####区画の右側####
		##################
		*/
		x = div->outer.right;
		// 部屋の高さ以内の範囲で接続点を探す（自区画から出ている経路の突き当りも含む）
		for ( y = div->inner.top; y <= div->inner.bottom; y++ ) {
			if ( layer( y, x ) == 0 ) {
				route_knots.push_back( y );
			}
		}

		// 部屋の高さ以内の範囲に接続点がなかった場合（１つしかなくてもまっすぐに他の部屋とつながっている場合は除く）
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

		// 接続点が2つ以上あればそれらを通路として結ぶ
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( x, route_knots.front(), x, route_knots.back(), 0 );
		// 接続点が1つしかないときは部屋までの通路を消す（周囲に空間が存在する場合を除く）
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
		####区画の下側####
		##################
		*/
		y = div->outer.bottom;
		// 部屋の幅以内の範囲で接続点を探す（自区画から出ている経路の突き当りも含む）
		for ( x = div->inner.left; x <= div->inner.right; x++ ) {
			if ( layer( y, x ) == 0 ) {
				route_knots.push_back( x );
			}
		}

		// 部屋の幅以内の範囲に接続点がなかった場合（１つしかなくてもまっすぐに他の部屋とつながっている場合は除く）
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

		// 接続点が2つ以上あればそれらを通路として結ぶ
		if ( route_knots.size() > 1 ) layer.fillRectLTRB( route_knots.front(), y, route_knots.back(), y, 0 );
		// 接続点が1つしかないときは部屋までの通路を消す（周囲に空間が存在する場合を除く）
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

	// 縦方向の接続点サーチ
	if ( vertical ) {
		int x = fixedPoint;
		int y;

		if ( from <= to ) {
			for ( y = from; y < to; y++ ) {
				// 空間が3つ以上続いている場合は通路を延ばすと部屋を貫通してしまうのでbreak
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
				// 空間が3つ以上続いている場合は通路を延ばすと部屋を貫通してしまうのでbreak
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
	} else { // 横方向のサーチ
		int y = fixedPoint;
		int x;

		if ( from <= to ) {
			for ( x = from; x < to; x++ ) {
				// 空間が3つ以上続いている場合は通路を延ばすと部屋を貫通してしまうのでbreak
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
				// 空間が3つ以上続いている場合は通路を延ばすと部屋を貫通してしまうのでbreak
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