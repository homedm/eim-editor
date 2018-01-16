#include <curses.h>
#include <ncurses.h>
#include <locale.h>
#include "enum.h"
#include "BufferClass.h"
#include "CommandLineClass.h"
#include "ScreenClass.h"

int main(int argc, char *argv[])
{
		ScreenClass screen;
		int key;
		// main loop
		while (true)
		{
				key = getch(); //キー入力
				screen.command_branch(key);
		}

		return 0;
}
