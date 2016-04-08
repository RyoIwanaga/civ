#ifndef _Console_h_
#define _Console_h_

#include <cassert>
#include "../World.h"
#include "../Util.h"

//#include "Window.h"

namespace Console {

#include <curses.h>

enum class Color : short {
	Player1 = 10,
	Player2,
	Player3,
	Player4,
	Player5,
	Player6,
	Player7,
	Player8,
};

short makeColorPlayer(ushort player)
{
	return player + 10;
}

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

	
	init_pair(static_cast<int>(Color::Player1), COLOR_WHITE, COLOR_BLUE);
	init_pair(static_cast<int>(Color::Player2), COLOR_WHITE, COLOR_RED);
	init_pair(static_cast<int>(Color::Player3), COLOR_WHITE, COLOR_YELLOW);
}

void finalize ()
{
	// Before exiting. Before the program is terminated, endwin() must be called to restore the terminal settings. 
	endwin();
}


} // end of namespace Console

#endif // _Console_h_

