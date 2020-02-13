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
	if ( size < ( MIN_ROOM_SIZE + OUTER_MERGIN * 2 ) * 2 ) return true;
	return false;
}

void DangeonGenerator::generate() {
	layer = new Layer2D( width, height );

	layer->fill( 0 ); // 指定サイズで初期化したlayerを壁で埋める
	//layer->Dump();

	createDivision( 0, 0, width - 1, height - 1 ); // 最初の親区画を生成
	roomNum += 1;

	srand( ( unsigned int )time( nullptr ) ); // 区画をさらに分割するかどうかの判断に乱数を用いるので初期化

	splitDivison( true );
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
	if ( roomNum >= MIN_ROOM_NUM && ( rand() % 100 + 1 ) <= ( int )( ( float )roomNum / MAX_ROOM_NUM ) * 100 ) {
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
	*/
	int a, b;
	if ( vertical ) {
		a = parentDiv->outer->top + ( MIN_ROOM_SIZE + OUTER_MERGIN );
		b = parentDiv->outer->bottom - ( MIN_ROOM_SIZE + OUTER_MERGIN );
	} else {
		a = parentDiv->outer->left + ( MIN_ROOM_SIZE + OUTER_MERGIN );
		b = parentDiv->outer->right - ( MIN_ROOM_SIZE + OUTER_MERGIN );
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

}