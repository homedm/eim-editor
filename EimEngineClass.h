// 他のウィンドウを管理するクラス
#ifndef _INC_SCREENCLASS
#define _INC_SCREENCLASS

#include <ncurses.h>
#include "enum.h"
#include "BufferClass.h"
#include "CommandLineClass.h"

class EimEngineClass
{
		private:
				BufferClass buffer_container[10];
				CommandLineClass command_line = CommandLineClass( newwin(3, COLS, LINES-2, 0) );
				int active_buffer_number;

		public:
				EimEngineClass();
				~EimEngineClass();
				int split_window();
				int command_branch(int key);

};

#endif //INC_SCREENCLASS
