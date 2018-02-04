// command line についてのクラス
#ifndef _INC_COMMANDLINECLASS
#define _INC_COMMANDLINECLASS
#include <ncurses.h>
#include <curses.h>
#include "enum.h"
#include <memory>
#include <vector>
#include "BufferClass.h"

class CommandLineClass // {{{
{
		private:
				WINDOW *win_ptr;

		public:
				CommandLineClass();
				~CommandLineClass();
				int command_branch(int); // active buffer number を渡す。
				int setWindow();

}; // }}}

#endif //INC_COMMANDLINECLASS
