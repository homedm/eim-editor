#include "CommandLineClass.h"
#include <ncurses.h>
#include "enum.h"
#include <cstdlib>

CommandLineClass::CommandLineClass()
{
}

CommandLineClass::~CommandLineClass()
{
		delwin(this->win_ptr);
}

int CommandLineClass::setWindow(){
		win_ptr = newwin(3, COLS, LINES-2, 0);

		wclear(win_ptr); // clear window
		scrollok(win_ptr, false); // scroll off

		wbkgd(win_ptr, COLOR_PAIR(1));
}

int CommandLineClass::command_branch()
{
	echo();
}
