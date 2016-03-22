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
// Hexverの陸地生成
// カーソルの移動
// マップのスクロール
//
//

int main () 
{
	auto world = World::createMassive(10, 15, true, 0.5f);

	Console::initialize();

	auto winMain = Console::createWindow(
			world->height * 2,
			world->width * 4 + 2,
			1, 1);

	Console::displayWorldHex(winMain, *world);

	wmove(winMain, 0, 0);
	wrefresh(winMain);

	int cursolX = 0;
	int cursolY = 0;
	bool isEndGame = false;

	for (;;) {
		wmove(winMain, cursolY, cursolX);
		wrefresh(winMain);

		int ch = getchar();
	
		switch (ch) {
		case 'k':
			cursolY --;
			break;
		case 'j':
			cursolY ++;
			break;
		case 'h':
			cursolX --;
			break;
		case 'l':
			cursolX ++;
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
