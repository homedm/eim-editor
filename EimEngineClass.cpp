// EimEngineClass.cpp
#include <ncurses.h>
#include <memory>
#include <locale.h>
#include "enum.h"
#include "EimEngineClass.h"
#include "BufferClass.h"

EimEngineClass::EimEngineClass()
{
		setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
		initscr();

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
						command_line.command_branch(); break;
				default:
						buff_container_ptr[active_buffer_number].get()->command_branch(key); break;
		}
		return 0;
}
