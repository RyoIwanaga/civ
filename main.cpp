#include <iostream>
#include <vector>
//#include <curses.h>

#include "World.h"
#include "Console/Console.h"
#include "Console/Window.h"
#include "Terrain.h"


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
// unit no hyouji
// 
//
// automake ソース整理
// console namespace
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
	auto winWorld = Console::WindowWorld::create(12, 22, 2, 2,
			// world size
			world->height, world->width, world->isCylinder);

	bool isEndGame = false;

	for (;;) {
		winWorld->display(*world);

		int ch = getchar();
	
		switch (ch) {
		case 'y':
			winWorld->moveLeftUp();
			break;
		case 'u':
			winWorld->moveRightUp();
			break;
		case 'b':
			winWorld->moveLeftDown();
			break;
		case 'n':
			winWorld->moveRightDown();
			break;
		case 'k':
			winWorld->moveLeftUp();
			break;
		case 'j':
			winWorld->moveRightDown();
			break;
		case 'h':
			winWorld->moveLeft();
			break;
		case 'l':
			winWorld->moveRight();
			break;
		case 'q':
			isEndGame = true;
		}

		if (isEndGame)
			break;
	}

	Console::finalize();

	return 0;	
}




/*
 * 1 2 3 4
 *  5 6 7 8
 * a b c d
 *  e f g h
 *
 *
 *
 *  5 5 x 6 6 x 7 7
 * 5 5 5 6 6 6 7 7 7
 *  5 5 x 6 6 x 7 7
 * a x b b x c c
 *  a b b b c c c
 * a x b b x c c
 *
 *
 *
 *      6 6 
 *     6 6 6 
 *  5 5 6 6
 * 5 5 5
 *  5 5
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
