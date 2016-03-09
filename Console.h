#ifndef _Console_h_
#define _Console_h_

#include "World.h"

namespace Console {

#include <curses.h>

char makeChLeftBottom(const Terrain& terrain);

void initialize()
{
	// The very first thing to do: Before you use any other curses routines, the initscr() routine must be called first.
	// If your program is going to write to several terminals, you should call newterm instead, which is another story.
	initscr(); 

	// One-character-a-time. To disable the buffering of typed characters by the TTY driver and get a character-at-a-time input, you need to call
    cbreak(); 

	// No echo. To suppress the automatic echoing of typed characters, you need to call
    noecho(); 

	// Special keys. In order to capture special keystrokes like Backspace, Delete and the four arrow keys by getch(), you need to call
	keypad(stdscr, TRUE); 

	start_color();


	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
}

void finalize ()
{
	// Before exiting. Before the program is terminated, endwin() must be called to restore the terminal settings. 
	endwin();
}

typedef WINDOW Window;

Window* createWindow(int height, int width, int y, int x)
{
	auto win = newwin(height, width, y, x);
	wrefresh(win);

	return win;
}

void moveAddCh(WINDOW* window, int y, int x, int n)
{
	mvwaddch(window, y, x, n);
}

void displayWorld(Window* window, const World& world)
{
	for (int col = 0; col < world.height * 3; col++) {

		wmove(window, col, 0);

		for (int row = 0; row < world.width * 3; row++) {
			switch (col	% 3) {
			case 0:
				// unit
				break;
			case 1: 
			{
				auto terrain = world.terrains[col / 3 * world.width + row / 3];

				switch (row % 3) {
				case 0: 
				{
					int color;


					if (terrain.base == Terrain::BaseType::Coast
							|| terrain.base == Terrain::BaseType::Ocean) {
						color = 3;
					}
					else if (terrain.feature == Terrain::FeatureType::Forest) {
						color = 2;
					}
					else {
						color = 1;
					}

					waddch(window, makeChLeftBottom(terrain) | COLOR_PAIR(color));
				}

					break;
				case 1:
					waddch(window, ' ');
					break;
				case 2:
					waddch(window, ' ');
					break;
				}
			}
				break;
			case 2:
				// blank line
				break;
			}
		}
	}

	wrefresh(window);
}

char makeChLeftBottom(const Terrain& terrain)
{
	switch (terrain.base) {
	case Terrain::BaseType::None:
		return '+';
	case Terrain::BaseType::Glassland:
		if (terrain.vertical == Terrain::VerticalType::Flatland)
			return 'v';
		else
			return '-';

	case Terrain::BaseType::Plains:
		if (terrain.vertical == Terrain::VerticalType::Flatland)
			return '.';
		else
			return '^';

	case Terrain::BaseType::Tundra:
		if (terrain.vertical == Terrain::VerticalType::Flatland)
			return 't';
		else
			return 'T';

	case Terrain::BaseType::Desert:
		if (terrain.vertical == Terrain::VerticalType::Flatland)
			return 'd';
		else
			return 'D';

	case Terrain::BaseType::Ice:
		return '*';

		//// Oceans ////
		
	case Terrain::BaseType::Coast:
	case Terrain::BaseType::Ocean:
		return '~';
	default:
		return '?';
	}
}

} // end of namespace Console

#endif // _Console_h_

