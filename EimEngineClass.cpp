// EimEngineClass.cpp
#include <ncurses.h>
#include <memory>
#include <locale.h>
#include "enum.h"
#include "EimEngineClass.h"
#include "BufferClass.h"

EimEngineClass::EimEngineClass()
{
	initscr();
	setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
	cbreak();
	//キー入力された文字を表示しないモードにする。初めはmove modeのため。
	noecho();
	keypad(stdscr, TRUE);

	// set color {{{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	// }}}

	// make commandline window buffer window
	add_buffer();
	command_line.setWindow();

	// for indicate active buffer
	active_buffer_number = 0;
}

EimEngineClass::~EimEngineClass()
{
	endwin(); //ncurses終了
}

int EimEngineClass::add_buffer(){
	this->buff_container_ptr.push_back(   std::unique_ptr<BufferClass>(  new BufferClass( newwin(LINES-3, COLS, 0, 0) )  )   );
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
			if(command_line.command_branch(active_buffer_number) == EXITPROGRAM){
				// exit program
				delete this;
			}
			; break;
		default:
			buff_container_ptr[active_buffer_number].get()->command_branch(key); break;
	}
	return 0;
}
