// BufferClass.cpp --- bufferのデータ管理
#include "../include/BufferClass.hpp"
#include "../include/enum.hpp"
#include <locale.h>
#include <ncurses.h>
#include <list>
#include <string>
#include <memory>
#include <fstream>

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
	delwin(win_ptr);
} // }}}

// getter and setter {{{
// mode {{{
Mode BufferClass::_get_mode(){
	return mode;
}
void BufferClass::_set_mode(Mode setmode) {
	mode = setmode;
} // }}}

// window_id {{{
WINDOW* BufferClass::_get_id(){
	return win_ptr;
}
// }}}

// filename {{{
std::string BufferClass::_get_filename(){
	return filename;
}
void BufferClass::_set_filename(std::string set_filename){
	filename = set_filename;
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
	cursor_x = set_cursor_x;
}
void BufferClass::_set_cursor_y(int set_cursor_y){
	cursor_y = set_cursor_y;
}
// }}}
// }}}

// move_y, move_xだけ現在のカーソルの位置を移動させる.
int BufferClass::move_cursor(int move_x, int move_y){ // {{{
	int lines, cols;
	getmaxyx(win_ptr, lines, cols);
	if(cursor_x + move_x <= cols-1 && cursor_x + move_x >= 0) cursor_x += move_x;
	if(cursor_y + move_y <= lines-1 && cursor_y + move_y >= 0) cursor_y += move_y;
	wmove(win_ptr, cursor_y, cursor_x);
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
		case '^':
			move_cursor(-cursor_x, 0);break;
		// }}}
		// print command {{{
		case 'i':
			printkey(); break;
		case 'a':
			move_cursor(-1, 0);
			printkey(); break;
		case 'R':
			int lines, cols;
			getmaxyx(win_ptr, lines, cols);
			printkey(cols - cursor_x); break;
		// }}}
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
				winsch(win_ptr, (char)key);
				move_cursor(1, 0);
		}
		wrefresh(win_ptr);
	}
}
// str文字だけ上書きする
int BufferClass::printkey(int str)
{
	int key;
	int i = 0;
	while ( i < str )
	{
		key = getch();
		switch( key )
		{
			case KEY_ESC:
				return 0;
				break;
			default:
				waddch(win_ptr, (char)key);
				move_cursor(1, 0);
		}
		wrefresh(win_ptr);
		++i;
	}
}

// ファイルをオープンし、それを一行ずつtextlistに入れる
int BufferClass::readfile(std::string const filename){ // {{{
	std::ifstream inputf(filename);

	std::string str;

	// textlistの最後尾から順に読み込んだテキストを格納する
	auto itr = textlist.end();
	while (getline(inputf, str)) {
		itr = textlist.insert(itr, str);
		++itr;
	}
	return 0;
} // }}}


int BufferClass::write2file(std::string const filename){ // {{{
	std::ofstream outputf(filename);

	for(auto itr = textlist.begin(); itr != textlist.end(); ++itr) {
		outputf << *itr;
		++itr;
	}
	return 0;
}
// }}}
