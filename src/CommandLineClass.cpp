// CommandLineClass.cpp --- Commandline$B$KF~NO$5$l$?%3%^%s%I$N=hM}(B
#include "../include/CommandLineClass.hpp"
#include "../include/BufferClass.hpp"
#include "../include/enum.hpp"
#include <ncurses.h>
#include <locale.h>
#include <cstdlib>
#include <vector>
#include <memory>
#include <string.h>

#define COMMANDLINEMAX 100
#define COMMANDMAX 20
#define OPTINOMAX 80

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
	wclear(win_ptr);
	wrefresh(win_ptr);

	char str[COMMANDLINEMAX], command[COMMANDMAX], option[OPTINOMAX];
	int key, i=0, iscmd=0;
	while(true){
		key = getch();

		switch(key) {
			case KEY_ESC:
				// return move mode
				return SUCCESS;
				break;
				// case KEY_ENTER:
			case '\n':
				// $B%3%^%s%I$NF~NO40N;(B
				// Enter key
				// $B%3%^%s%I%i%$%s$KF~NO$5$l$?%3%^%s%I$rFI$_9~$`(B {{{
				// $BF~NO$5$l$?J8;zNs$rJ,3d$9$k(B
				parse(str, command, option);
				if(strcmp(command,"q") || strcmp(command, "quit"))
				{
					// $B%W%m%0%i%`$r40A4$K=*N;$5$;$k(B
					return EXITPROGRAM;

				}
				else if( strcmp(command, "e") || strcmp(command, "edit") )
				{
					// $B?7$7$/%U%!%$%k$r3+$$$F!"%P%C%U%!!<$rA}$d$9(B
				}
				// }}}

				wclrtobot(win_ptr);
				wrefresh(win_ptr);

				return SUCCESS;
				break;
			default :
				waddch(win_ptr, (char)key);
				// $BF~NO$5$l$?J8;z$rJ];}$9$k(B
				if( i < COMMANDLINEMAX)
				{
					str[i] = key;
					i++;
				}
		}
		wrefresh(win_ptr);
	}
	return SUCCESS;
}

int CommandLineClass::parse(const char *str, char *command, char *option)
{
	int i;
	for(i=0; i < strlen(str); i++)
	{
		if (str[i] == ' ') { i++; break; }
		command[i] = str[i];
	}
	// i$B$O(Boption$B$NF,$N0LCV$r;X$9(B
	int j = 0;
	for(; i < strlen(str); i++)
	{
		option[j] = str[i];
		j++;
	}
	return SUCCESS;
}
