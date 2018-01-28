// 他のウィンドウを管理するクラス
#ifndef _INC_SCREENCLASS
#define _INC_SCREENCLASS

#include <ncurses.h>
#include <stdio.h>
#include <memory>
#include "enum.h"
#include "BufferClass.h"
#include "CommandLineClass.h"

class EimEngineClass
{
		private:

		public:
				EimEngineClass();
				~EimEngineClass();
				int split_window();
				int command_branch(int key);

};

#endif //INC_SCREENCLASS
