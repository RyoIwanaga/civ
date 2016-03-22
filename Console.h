#ifndef _Console_h_
#define _Console_h_

#include "World.h"

namespace Console {

#include <curses.h>


class Window
{
public:
	typedef std::shared_ptr<Window> Ptr;

	WINDOW* window;
	int height;
	int width;
	int y;
	int x;

	Window(int h, int w, int y, int x) :
		height(h),
		width(w),
		y(y),
		x(x)
	{
		window = newwin(height, width, y, x);
	}

	~Window()
	{
		delwin(window);
	}

	static Ptr create(int h, int w, int y, int x)
	{
		return std::make_shared<Window>(h, w, y, x);
	}
};

char makeChLeftBottom(const Terrain& terrain);

class WindowWorld : public Window
{
public:
	typedef std::shared_ptr<WindowWorld> Ptr;

	WindowWorld(int h, int w, int y, int x) :
		Window(h, w, y, x)
	{}

	static Ptr create(int h, int w, int y, int x)
	{
		return std::make_shared<WindowWorld>(h, w, y, x);
	}

	void display(const World& world)
	{
		/* oo  oo
		 * oo  oo
		 *   oo  oo
		 *   oo  oo
		 * oo  oo
		 * oo  oo
		 */
		for (int y = 0; y < world.height * 2; y++) {

			switch (y % 4) {
			case 0:
			case 1:
				wmove (window, y, 0);
				break;
			case 2:
			case 3:
				wmove (window, y, 2);
				break;
			}

			for (int x = 0; x < world.width * 4; x++) {

				auto terrain = world.terrains[y / 2 * world.width + x / 4];

				switch (x % 4) {
				case 0:
				case 1: {
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
				case 2:
				case 3:
						waddch(window, ' ');
						break;
				}
			}
		}

		wrefresh(window);
	}
};


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

