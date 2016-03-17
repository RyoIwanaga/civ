#include <iostream>
#include <vector>
//#include <curses.h>

#include "Console.h"
#include "Terrain.h"
#include "World.h"


// 洗濯する楽しみはある
// 	手段の豊富さ
// 	でも、操作量が増えないように
//
// 戦闘はHomm
// Unitがスタック
// 拠点がユニットを毎ターン生み出す？
// 戦闘はsquare
// 	主力スタックだけになってしまう
// 	移動力が同じになってしまう
//	地形効果が出しづらい
//	戦果が予測しづらい
// マルチプレイできない
//
// Field をHexにするか？　
//
//// TODO
//
// カーソルの移動
// マップのスクロール
//
//

int main () 
{
	auto world = World::createMassive(10, 15, true, 0.3f);

	Console::initialize();

	auto winMain = Console::createWindow(
			world->height * 2,
			world->width * 4 + 2,
			1, 1);

	Console::displayWorldHex(winMain, *world);

	while (getchar() == ERR) {
	
	}

	Console::finalize();

	return 0;	
}
