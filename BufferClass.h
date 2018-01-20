// 個々のbufferについて管理するクラス
#ifndef _INC_BUFFERCLASS
#define _INC_BUFFERCLASS
#include <ncurses.h>
#include <string>
#include <list>
#include "enum.h"

class BufferClass // {{{
{
		private:
				Mode mode;
				WINDOW *id;
				std::list<char> textlist; // テキストファイルを一行ごとに保持する
				std::string filename;
		
		// construter
		public:
				BufferClass();
				~BufferClass();
				Mode _get_mode();
				void _set_mode(Mode setmode);
				WINDOW _get_id();
				void _set_id(WINDOW setid);
				int move_cursor(int move_y, int move_x);
				int command_branch(int key);
				int readfile(char openfilename);

}; // }}}

#endif //INC_BUFFERCLASS
