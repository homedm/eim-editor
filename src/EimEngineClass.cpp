// EimEngineClass.cpp --- commandline, bufferに対する操作を行う
#include <ncurses.h>
#include <locale.h>
#include <memory>
#include <locale.h>
#include "../include/enum.hpp"
#include "../include/EimEngineClass.hpp"
#include "../include/BufferClass.hpp"

EimEngineClass::EimEngineClass()
{
	setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
	initscr();
	cbreak();
	//キー入力された文字を表示しないモードにする。初めはmove modeのため。
	noecho();
	keypad(stdscr, TRUE);

	// set color {{{
	start_color();
	// init_pair(number, foreground, background);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_GREEN, COLOR_RED);
	curs_set(1);
	// }}}

	// make commandline window buffer window
	add_buffer();
	command_line.setWindow();

	// for indicate active buffer
	active_buffer_number = 0;
}

EimEngineClass::~EimEngineClass()
{
	// バッファーオブジェクトを開放する。
	for(int i=0;buff_container_ptr.size(); i++)
	{
		delete buff_container_ptr[i].get();
	}
	endwin(); //ncurses終了
}

int EimEngineClass::add_buffer(){
	this->buff_container_ptr.push_back(   std::unique_ptr<BufferClass>(  new BufferClass( newwin(LINES-3, COLS, 0, 0) )  )   );
}

int EimEngineClass::split_window(){
	//ウィンドウを均一に横に分割する
	// 未実装
	return 0;
}

int EimEngineClass::command_branch(int key)
{
	// 返り値によって　処理を分岐する
	switch (key) {
		case ':':
			// change command mode
			buff_container_ptr[active_buffer_number].get()->_set_mode(COMMANDMODE);
			switch(command_line.command_branch(active_buffer_number))
			{
				case EXITPROGRAM:
					// exit program
					delete this;
					break;

				case CHANGEMOVEMODE:
					buff_container_ptr[active_buffer_number].get()->_set_mode(MOVEMODE);
					break;

			}
			break;
			// move mode command branch
		default:
			buff_container_ptr[active_buffer_number].get()->command_branch(key);
			break;
	}
	buff_container_ptr[active_buffer_number].get()->_set_mode(MOVEMODE);
	return 0;
}
