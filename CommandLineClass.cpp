#include "CommandLineClass.h"
#include "BufferClass.h"
#include <ncurses.h>
#include "enum.h"
#include <cstdlib>
#include <vector>
#include <memory>

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

	wbkgd(win_ptr, 2);
}
int CommandLineClass::command_branch(int active_buffer_number)
{
	// focus on command line window
	move(LINES-2, 0);
	nocbreak();
	echo();

	int key;
	while(true){
		key = getch();

		if ( key == KEY_ESC){
			return EXITPROGRAM;
		} else {
			waddch(win_ptr, (char)key);
		}
		wrefresh(win_ptr);
	}
}
