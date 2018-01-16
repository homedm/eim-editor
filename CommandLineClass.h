// command line についてのクラス
#ifndef _INC_COMMANDLINECLASS
#define _INC_COMMANDLINECLASS
#include <ncurses.h>
#include "enum.h"

class CommandLineClass // {{{
{
		private:
				WINDOW *window_id;
		public:
				CommandLineClass(WINDOW *window_name);
				~CommandLineClass();
}; // }}}

#endif //INC_COMMANDLINECLASS
