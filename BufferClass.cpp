#include "BufferClass.h"
#include <ncurses.h>
#include <list>
#include <string>
#include <memory>
#include "enum.h"

BufferClass::BufferClass(WINDOW *win_ptr) // {{{
{
		mode = MOVEMODE;

		wclear(win_ptr); //画面表示
		cbreak();

		start_color();

		//キー入力された文字を表示しないモードにする。初めはmove modeのため。
		noecho();
} // }}}

BufferClass::~BufferClass() // {{{
{
		// EimEngineClassのo_buffer_windowからも消す処理を追加する.
		delwin(this -> win_ptr);
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
		getmaxyx(this->win_ptr, cursor_y, cursor_x);
		wmove(this->win_ptr, cursor_y + move_y, cursor_x + move_x);
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
int BufferClass::readfile(std::string filename){ // {{{
		std::ifstream ifs(openfilename); // file open {{{
		if(!ifs) {
				// faild to open file
		}

		textlist.push_back("top");

		while (ifs.get(c)){
				textlist.push_back(c); // 末尾に追加
		}

		textlist.push_back("end");

		ifs.close(); // file close }}}
		return 0;
} // }}}


int BufferClass::write2file(std::filename){ // {{{
		for(auto itr = lst.begin(); itr != textlist.end(); ++itr) {
				printw(*itr << "\n");
		}
}
// }}}
