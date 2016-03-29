#include <iostream>
#include <vector>
//#include <curses.h>

#include "Console.h"
#include "Window.h"
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
//// TODO
//
// マップのスクロール
// automake ソース整理
//
//

int main () 
{
	auto world = World::createMassive(16, 30, true, 0.5f);

	Console::initialize();

//	auto winWorld = Console::WindowWorld::create(
//			world->height * 2,
//			world->width * 4 + 2,
//			2, 2,
//			world->height, world->width);
	auto winWorld = Console::WindowWorld::create(
			// size
			12, 22,
			//9, 13,
			// upper left
			2, 2,
			// world size
			world->height, world->width);

	bool isEndGame = false;

	for (;;) {
		winWorld->display(*world);

		int ch = getchar();
	
		switch (ch) {
		case 'k':
			//winWorld->y--;
			break;
		case 'j':
			break;
		case 'h':
			break;
		case 'l':
			break;
		default:
			isEndGame = true;
		}

		if (isEndGame)
			break;
	}

	Console::finalize();

	return 0;	
}
