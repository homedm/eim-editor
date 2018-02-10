// BufferClass.cpp --- bufferのデータ管理
#include "../include/BufferClass.hpp"
#include <locale.h>
#include <ncurses.h>
#include <list>
#include <string>
#include <memory>
#include <fstream>
#include "../include/enum.hpp"

BufferClass::BufferClass(WINDOW *win) // {{{
{
	win_ptr = win;
	mode = MOVEMODE;

	wclear(win_ptr); // clear buffer window
	cursor_x = 0; cursor_y = 0;

} // }}}

BufferClass::~BufferClass() // {{{
{
	// EimEngineClassのo_buffer_windowからも消す処理を追加する.
	delwin(this -> win_ptr);
} // }}}

// getter and setter {{{
// mode {{{
Mode BufferClass::_get_mode(){
	return this -> mode;
}
void BufferClass::_set_mode(Mode setmode) {
	this -> mode = setmode;
} // }}}

// window_id {{{
WINDOW* BufferClass::_get_id(){
	return this -> win_ptr;
}
// }}}

// filename {{{
std::string BufferClass::_get_filename(){
	return this -> filename;
}
void BufferClass::_set_filename(std::string set_filename){
	this -> filename = set_filename;
}
// }}}

// get cursor_? {{{
int BufferClass::_get_cursor_x(){
	return cursor_x;
}
int BufferClass::_get_cursor_y(){
	return cursor_y;
}
void BufferClass::_set_cursor_x(int set_cursor_x){
	this -> cursor_x = set_cursor_x;
}
void BufferClass::_set_cursor_y(int set_cursor_y){
	this -> cursor_y = set_cursor_y;
}
// }}}
// }}}

// move_y, move_xだけ現在のカーソルの位置を移動させる.
int BufferClass::move_cursor(int move_x, int move_y){ // {{{
	wchgat(win_ptr, 1, A_NORMAL, 0, 0);
	cursor_x += move_x;
	cursor_y += move_y;
	wmove(win_ptr, cursor_y, cursor_x);
	wchgat(win_ptr, 2, A_STANDOUT, 0, 0);
} // }}}

int BufferClass::command_branch(int const key) // {{{
{
	switch (key) {
		// move command {{{
		case 'h':
			// move left
			move_cursor(-1, 0); break;
		case 'j':
			//move down
			move_cursor(0, 1); break;
		case 'k':
			// move up
			move_cursor(0, -1); break;
		case 'l':
			// move right
			move_cursor(1, 0); break;
		// }}}
		case 'i':
			// until tap ESC key
			printkey();
			break;
	}

	wrefresh(win_ptr);
} // }}}

// print key
int BufferClass::printkey()
{
	int key;
	while (true)
	{
		key = getch();
		switch( key )
		{
			case KEY_ESC:
				return 0;
				break;
			default:
				waddch(win_ptr, (char)key);
		}
		wrefresh(win_ptr);
	}
}

// ファイルをオープンし、それを一行ずつtextlistに入れる
int BufferClass::readfile(std::string const filename){ // {{{
	std::ifstream inputf(filename);

	std::string str;

	// textlistの最後尾から順に読み込んだテキストを格納する
	auto itr = this -> textlist.end();
	while (getline(inputf, str)) {
		itr = textlist.insert(itr, str);
		++itr;
	}
	return 0;
} // }}}


int BufferClass::write2file(std::string const filename){ // {{{
	std::ofstream outputf(filename);

	for(auto itr = this -> textlist.begin(); itr != this->textlist.end(); ++itr) {
		outputf << *itr;
		++itr;
	}
	return 0;
}
// }}}
