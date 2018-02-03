#include "BufferClass.h"
#include <ncurses.h>
#include <list>
#include <string>
#include <memory>
#include <fstream>
#include "enum.h"

BufferClass::BufferClass(WINDOW *win) // {{{
{
	win_ptr = win;
	mode = MOVEMODE;

	wclear(win_ptr); // clear buffer window

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
// }}}

// move_y, move_xだけ現在のカーソルの位置を移動させる.
int BufferClass::move_cursor(int move_y, int move_x){ // {{{
	int cursor_y, cursor_x;
	getmaxyx(this->win_ptr, cursor_y, cursor_x);
	wmove(this->win_ptr, cursor_y + move_y, cursor_x + move_x);
} // }}}

int BufferClass::command_branch(int const key) // {{{
{
	switch (key) {
		case 'h':
			// move left
			move_cursor(0, -1); break;
		case 'j':
			//move down
			move_cursor(1, 0); break;
		case 'k':
			// move up
			move_cursor(-1, 0); break;
		case 'l':
			// move right
			move_cursor(0, 1); break;
	}

	wrefresh(win_ptr);
} // }}}

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
