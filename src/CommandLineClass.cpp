// CommandLineClass.cpp --- Commandlineに入力されたコマンドの処理
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
				// コマンドの入力完了
				// Enter key
				// コマンドラインに入力されたコマンドを読み込む {{{
				// 入力された文字列を分割する
				parse(str, command, option);
				if(strcmp(command,"q") || strcmp(command, "quit"))
				{
					// プログラムを完全に終了させる
					return EXITPROGRAM;

				}
				else if( strcmp(command, "e") || strcmp(command, "edit") )
				{
					// 新しくファイルを開いて、バッファーを増やす
				}
				// }}}

				wclrtobot(win_ptr);
				wrefresh(win_ptr);

				return SUCCESS;
				break;
			default :
				waddch(win_ptr, (char)key);
				// 入力された文字を保持する
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
	// iはoptionの頭の位置を指す
	int j = 0;
	for(; i < strlen(str); i++)
	{
		option[j] = str[i];
		j++;
	}
	return SUCCESS;
}
