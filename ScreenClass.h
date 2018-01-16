// 他のウィンドウを管理するクラス
#ifndef _INC_SCREENCLASS
#define _INC_SCREENCLASS

#include <ncurses.h>
#include "enum.h"
#include "BufferClass.h"
#include "CommandLineClass.h"

class ScreenClass 
{
		private:
				WINDOW *v_command_window;
				BufferClass* o_buffer_container[10];
				CommandLineClass* o_command_line;
				int o_active_buffer_number;

		public:
				ScreenClass();
				~ScreenClass();
				int split_window();
				int command_branch(int key);

};

#endif //INC_SCREENCLASS
