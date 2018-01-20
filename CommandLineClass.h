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
				CommandLineClass();
				~CommandLineClass();
}; // }}}

#endif //INC_COMMANDLINECLASS
