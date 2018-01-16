// 個々のbufferについて管理するクラス
#ifndef _INC_BUFFERCLASS
#define _INC_BUFFERCLASS
#include <ncurses.h>
#include "enum.h"

class BufferClass // {{{
{
		private:
				Mode mode;
				WINDOW *window_id;
		
		// construter
		public:
				BufferClass();
				~BufferClass();
				Mode _get_mode();
				void _set_mode(Mode setmode);
				int move_cursor(int move_y, int move_x);
				int command_branch(int key);

}; // }}}

#endif //INC_BUFFERCLASS
