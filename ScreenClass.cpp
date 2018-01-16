// ScreenClass.cpp
#include "enum.h"
#include "ScreenClass.h"
#include <ncurses.h>
#include <locale.h>

ScreenClass::ScreenClass()
{
		setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
		initscr();

		// make window
		// commnad line window
		v_command_window = newwin(3, COLS, LINES-2, 0);
		//buffer windwo
		o_buffer_container[0](newwin(LINES-3, COLS, 0, 0));
		o_command_line = CommandLineClass();
		o_active_buffer_number = 0;
}

ScreenClass::~ScreenClass()
{
		endwin(); //ncurses終了
}

int ScreenClass::split_window(){
		//ウィンドウを均一に横に分割する
}

int ScreenClass::command_branch(int key)
{
		switch (key) {
				case ':': 
						// change command mode
						this.o_command_line.command_branch(); break;
				default: 
						this.o_buffer_container[o_active_buffer_number].command_branch(key); break;
		}
}
