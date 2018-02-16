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
	command_line.~CommandLineClass();
}

int EimEngineClass::add_buffer(){
	this->buff_container_ptr.push_back(   std::shared_ptr<BufferClass>(  new BufferClass( newwin(LINES-3, COLS, 0, 0) )  )   );
}

int EimEngineClass::split_window(){
	//ウィンドウを均一に横に分割する
	// 未実装
	return 0;
}

int EimEngineClass::command_branch(const int key)
{
	// 返り値によって　処理を分岐する
	switch (key) {
		case ':':
			// change mode to command mode
			buff_container_ptr[active_buffer_number].get()->_set_mode(COMMANDMODE);

			// command mode command branch

			// アクティブバッファのインスタンスへのポインタをcommandlineに渡す
			switch( command_line.command_branch( buff_container_ptr[active_buffer_number] ) )
			{
				// 成功時
				case TRUE:
					break;
				case EXITPROGRAM:
					// プログラム終了
					return EXITPROGRAM;
					break;
			}
			// change mode to move mode
			buff_container_ptr[active_buffer_number].get()->_set_mode(MOVEMODE);
			break;
		default:
			// move mode command branch
			buff_container_ptr[active_buffer_number].get()->command_branch(key);
			break;
	}

	return 0;
}
