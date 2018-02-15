// CommandLineClass.cpp --- Commandline$B$KF~NO$5$l$?%3%^%s%I$N=hM}(B
#include "../include/CommandLineClass.hpp"
#include "../include/BufferClass.hpp"
#include "../include/enum.hpp"
#include <ncurses.h>
#include <locale.h>
#include <cstdlib>
#include <vector>
#include <memory>

CommandLineClass::CommandLineClass()
{
}

CommandLineClass::~CommandLineClass()
{
	delwin(win_ptr);
}

int CommandLineClass::setWindow(){
	win_ptr = newwin(2, COLS, LINES-2, 0);

	wclear(win_ptr); // clear window
	scrollok(win_ptr, false); // scroll off

	wbkgd(win_ptr, 2);
}

int CommandLineClass::command_branch( std::shared_ptr<BufferClass> buffer )
{
	// focus on command line window
	wmove(win_ptr, 0, 0);
	wrefresh(win_ptr);

	int key;
	while(true){
		key = getch();

		switch(key) {
			case KEY_ESC:
				// return move mode
				return SUCCESS;
				break;
			case KEY_ENTER:
				// $B%3%^%s%I$NF~NO40N;(B
				// Enter key
				read_command();
				break;
			default :
				waddch(win_ptr, (char)key);
				wrefresh(win_ptr);
		}
	}
	return SUCCESS;
}

int CommandLineClass::read_command()
{
	// $B%3%^%s%I%i%$%s$KF~NO$5$l$?%3%^%s%I$rFI$_9~$`(B {{{
	char command[20];
	wmove(win_ptr, 0, 0);
	wgetnstr(win_ptr, command, 20);
	if(command == "q") {
		return SUCCESS;
	}
	else if(command == "e" || command == "edit") {
	}
	// }}}
	wclear(win_ptr);
}
