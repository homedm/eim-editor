#include <curses.h>
#include <ncurses.h>
#include <locale.h>
#include <vector>
#include <memory>
#include "enum.h"
#include "BufferClass.h"
#include "CommandLineClass.h"
#include "EimEngineClass.h"

int main(int argc, char *argv[])
{
		EimEngineClass eimEngine;

		/* バッファ管理のためのコンテナを宣言 */
		/* get()メソッドを使って参照する必要がある。 */
		std::vector<std::unique_ptr<BufferClass>> buff_container_ptr;

		/* 初めのバッファーを作る */
		buff_container_ptr.push_back(   std::unique_ptr<BufferClass>(  new BufferClass( newwin(LINES-3, COLS, 0, 0) )  )   );

		int active_buffer_number = 0;

		/* コマンドラインスクリーンのクラスを宣言 */
		CommandLineClass command_line = CommandLineClass( newwin(3, COLS, LINES-2, 0) );

		int key; // 入力キーを保持するための変数

		// main loop
		while (true)
		{
				key = getch(); //キー入力
				eimEngine.command_branch(key);
		}

		return 0;
}
