// command line についてのクラス
#ifndef _INC_COMMANDLINECLASS
#define _INC_COMMANDLINECLASS
#include <ncurses.h>
#include "enum.h"

class CommandLineClass // {{{
{
		private:
				WINDOW *win_ptr;

		public:
				CommandLineClass();
				~CommandLineClass();
				int command_branch();
				int setWindow();

}; // }}}

#endif //INC_COMMANDLINECLASS
