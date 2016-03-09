#include <iostream>
#include <vector>
//#include <curses.h>

#include "Console.h"
#include "Terrain.h"
#include "World.h"

// 自動生成 まずはriku or umi

int main () 
{
	auto world = World::createMassive(5, 5, true, 0.5f);

	Console::initialize();

	auto winMain = Console::createWindow(
			world->height * 2 + world->height - 1,
			world->width * 2 + world->width - 1,
			1, 1);

	Console::displayWorld(winMain, *world);

	while (getchar() == ERR) {
	
	}

	Console::finalize();

	return 0;	
}
