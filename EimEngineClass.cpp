// EimEngineClass.cpp
#include "enum.h"
#include "EimEngineClass.h"
#include <ncurses.h>
#include <locale.h>

EimEngineClass::EimEngineClass()
{
		setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
		initscr();

		// make window
		buffer_container[0] = newwin(LINES-3, COLS, 0, 0);
		active_buffer_number = 0;
}

EimEngineClass::~EimEngineClass()
{
		endwin(); //ncurses終了
}

int EimEngineClass::split_window(){
		//ウィンドウを均一に横に分割する
}

int EimEngineClass::command_branch(int key)
{
		switch (key) {
				case ':': 
						// change command mode
						this.o_command_line.command_branch(); break;
				default: 
						this.o_buffer_container[o_active_buffer_number].command_branch(key); break;
		}
}
