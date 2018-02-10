// 個々のbufferについて管理するクラス
#ifndef _INC_BUFFERCLASS
#define _INC_BUFFERCLASS
#include <ncurses.h>
#include <curses.h>
#include <string>
#include <list>
#include "enum.hpp"

class BufferClass // {{{
{
		private:
				Mode mode;
				WINDOW *win_ptr;
				std::list<std::string> textlist; // テキストファイルを一行ごとに保持する
				std::string filename;
				int cursor_x, cursor_y; // the position in window

		// construter
		public:
				BufferClass(WINDOW *window_name);
				~BufferClass();
				// getter and setter {{{
				Mode _get_mode();
				void _set_mode(Mode setmode);

				WINDOW* _get_id();
				// void _set_id(WINDOW *setid);

				std::string _get_filename();
				void _set_filename(std::string);

				int _get_cursor_x();
				int _get_cursor_y();
				void _set_cursor_x(int);
				void _set_cursor_y(int);
				// }}}

				// cursor movement
				int move_cursor(int move_y, int move_x);
				int printkey();

				int command_branch(int key);

				// command for file
				int readfile(std::string const);
				int write2file(std::string const);

}; // }}}

#endif //INC_BUFFERCLASS
