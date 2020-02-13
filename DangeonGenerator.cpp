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
	// 2部屋分の余裕があるか
	if ( size < ( MIN_ROOM_SIZE + OUTER_MERGIN ) * 2 + OUTER_MERGIN / 2 * 3 ) return true;
	return false;
}

void DangeonGenerator::generate() {
	//printfDx( "width = %d\nheight = %d\n", width, height );
	layer = new Layer2D( width, height );

	layer->fill( 2 ); // 指定サイズで初期化したlayerを壁で埋める
	//layer->Dump();

	divisions.clear();
	roomNum = 0;

	createDivision( 0, 0, width - 1, height - 1 ); // 最初の親区画を生成
	roomNum += 1;

	srand( ( unsigned int )time( nullptr ) ); // 区画をさらに分割するかどうかの判断に乱数を用いるので初期化

	splitDivison( true );

	createRoom();

	layer->Dump();
}

// 指定範囲で区画を生成し，divisionsに追加
void DangeonGenerator::createDivision( int left, int top, int right, int bottom ) {
	DangeonDivision* division = new DangeonDivision();
	division->outer->set( left, top, right, bottom );
	divisions.push_back( division );
}


// 区画を分割していく（引数：verticalで垂直分割から始めるか決める，falseなら水平分割から）
/*
	分割されてできた2区画に対して再帰的にsplitDivision()を行う
	確率，または部屋の広さ制限に応じて分割を止める
*/
void DangeonGenerator::splitDivison( bool vertical ) {
	// divisionsの末尾から親となる要素を取り出す
	DangeonDivision* parentDiv = divisions.back();//divisions[(int)divisions.size()];
	divisions.pop_back();

	//printfDx( "%d\n", parentDiv->outer->getWidth() );

	/* 
		親を分割できる，または確立によって分割するのか決定
		ここにおける確率はdivisionsのサイズ，つまり現在の部屋数に応じて変動するのがよさそう？
		分割できなければdivisonsに親を戻してreturn
	*/
	// 分割方向(vertical)に応じて分割可能かチェック
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
		a = parentDiv->outer->top + ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
		b = parentDiv->outer->bottom - ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
	} else {
		a = parentDiv->outer->left + ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
		b = parentDiv->outer->right - ( MIN_ROOM_SIZE + OUTER_MERGIN / 2 * 3 );
	}
	int ab = b - a; // a, b間の距離
	int p = a + rand() % ( ab + 1 );

	/* 
		子の区画を生成
		分割方向に応じて親の区画を縮める
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
	各区画ごとに部屋を生成
	1. 部屋の大きさをランダムに決める(OUTER_MERGINを考慮)
	2. 部屋の大きさを考慮して区画内での配置場所をランダムに決定
	3. 確定した部屋の範囲を通路で埋める
*/
void DangeonGenerator::createRoom() {
	for ( DangeonDivision* div : divisions ) {
		int max_room_width = div->outer->getWidth() - OUTER_MERGIN * 2; // 部屋の幅の最大値
		int max_room_height = div->outer->getHeight() - OUTER_MERGIN * 2; // 部屋の高さの最大値

		int room_width = rand() % ( max_room_width - MIN_ROOM_SIZE + 1 ) + MIN_ROOM_SIZE; // 部屋の幅
		int room_height = rand() % ( max_room_height - MIN_ROOM_SIZE + 1 ) + MIN_ROOM_SIZE; // 部屋の高さ

		/*
			親と子が6を境界線として下記のように分割されていた時，
			左側の区画では(0, 1)をマージン，(2, 4)を部屋，(5, 6)をマージンとしたいので
			以下のように基準点(room_x, room_y)を求める
			0 1 2 3 4 5 6 7 8 9 10 11 12
			            6
		*/
		int room_x = rand() % ( div->outer->getWidth() - OUTER_MERGIN *2 - room_width + 1 ) + OUTER_MERGIN; // 部屋のx座標（左上）
		int room_y = rand() % ( div->outer->getHeight() - OUTER_MERGIN *2 - room_height + 1 ) + OUTER_MERGIN; // 部屋のy座標（左上）

		int left = div->outer->left + room_x;
		int top = div->outer->top + room_y;
		int right = left + room_width - 1;
		int bottom = top + room_height - 1;
		// 0 1 2 3
		// 0 1 2 3 4 5 6 7 8
		// 1 2 3 4 5 6 7 8 9
		//   2 3 4 5
		div->inner->set( left, top, right, bottom );

		layer->fillRectLRTB( div->outer->left, div->outer->top, div->outer->right, div->outer->bottom, 2 );
		layer->fillRectLRTB( div->outer->left+1, div->outer->top+1, div->outer->right-1, div->outer->bottom-1, 1 );
		fillRoom( div->inner );
	}
}

void DangeonGenerator::fillRoom( DangeonDivision::DangeonRectangle* inner ) {
	layer->fillRectLRTB( inner->left, inner->top, inner->right, inner->bottom, 0 );
}