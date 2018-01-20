#include "BufferClass.h"
#include <ncurses.h>
#include <list>
#include <string>
#include <fstream.h>
#include "enum.h"

BufferClass::BufferClass(WINDOW *window_name) // {{{
{
		mode = MOVEMODE;
		window_id = window_name;

		wclear(window_id); //画面表示
		cbreak();

		start_color();

		//キー入力された文字を表示しないモードにする。初めはmove modeのため。
		noecho();
} // }}}

BufferClass::~BufferClass() // {{{
{
		// EimEngineClassのo_buffer_windowからも消す処理を追加する.
		delwin(this -> window_id);
} // }}}


// getter
Mode BufferClass::_get_mode(){ // {{{
		return this -> mode;
}
// setter
void BufferClass::_set_mode(Mode setmode) {
		this -> mode = setmode;
} // }}}

// move_y, move_xだけ現在のカーソルの位置を移動させる.
int BufferClass::move_cursor(int move_y, int move_x){ // {{{
		int cursor_y, cursor_x;
		getmaxyx(this->window_id, cursor_y, cursor_x);
		wmove(this->window_id, cursor_y + move_y, cursor_x + move_x);
} // }}}

int BufferClass::command_branch(int key) // {{{
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
} // }}}

// ファイルをオープンし、それを一行ずつtextlistに入れる
int BufferClass::readfile(std::string openfilename){ // {{{
		std::ifstream ifs(openfilename); // file open {{{
		if(!ifs) {
				// faild to open file
		}

		while (ifs.get(c)){
				textlist.push_back(c); // 末尾に追加
		}

		ifs.close(); // file close }}}
		return 0;
} // }}}


// draw
int BufferClass::drawfile(){
}

