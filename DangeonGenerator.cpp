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

	/*
		分割が可能であればchildDiv_a, childDiv_bを生成
		childDiv_aをdivisionsに加えてからsplitDivisionを呼び出す
		その後，childDiv_bをdivisionsに加えてsplitDivisionを呼び出す

		こうすることでchildDiv_aを親としてさらに分割していく処理が終わってから
		childDiv_bを親として分割する処理に入ることができる
	*/
}

