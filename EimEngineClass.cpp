// EimEngineClass.cpp
#include "enum.h"
#include "EimEngineClass.h"
#include <ncurses.h>
#include <memory>
#include <locale.h>

EimEngineClass::EimEngineClass()
{
		setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
		initscr();

}

EimEngineClass::~EimEngineClass()
{
		endwin(); //ncurses終了
}

int EimEngineClass::split_window(){
		//ウィンドウを均一に横に分割する
		return 0;
}

int EimEngineClass::command_branch(int key)
{
		switch (key) {
				case ':':
						// change command mode
						command_line.command_branch(); break;
				default:
						buffer_container[active_buffer_number].command_branch(key); break;
		}
		return 0;
}
