// 他のウィンドウを管理するクラス
#ifndef _INC_SCREENCLASS
#define _INC_SCREENCLASS
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <memory>
#include <vector>
#include "enum.hpp"
#include "BufferClass.hpp"
#include "CommandLineClass.hpp"

class EimEngineClass
{
	private:
		/* バッファ管理のためのコンテナを宣言 */
		/* get()メソッドを使って参照する必要がある。 */
		std::vector<std::unique_ptr<BufferClass>> buff_container_ptr;

		int active_buffer_number;

		CommandLineClass command_line;

	public:
		EimEngineClass();
		~EimEngineClass();

		int add_buffer();
		int split_window();
		int command_branch(int key);
};

#endif //INC_SCREENCLASS
