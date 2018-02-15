// command line についてのクラス
#ifndef _INC_COMMANDLINECLASS
#define _INC_COMMANDLINECLASS
#include <ncurses.h>
#include <curses.h>
#include "enum.hpp"
#include <memory>
#include <vector>
#include "BufferClass.hpp"

class CommandLineClass // {{{
{
		private:
				WINDOW *win_ptr;
				std::shared_ptr<BufferClass> buffer;

		public:
				CommandLineClass();
				~CommandLineClass();
				int command_branch(std::shared_ptr<BufferClass>); // active buffer number を渡す。
				int setWindow();
				int read_command();
				int parse(const char*, char*, char*);

}; // }}}

#endif //INC_COMMANDLINECLASS
