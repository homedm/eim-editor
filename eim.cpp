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


		int key; // 入力キーを保持するための変数

		// main loop
		while (true)
		{
				key = getch(); //キー入力
				eimEngine.command_branch(key);
		}

		return 0;
}
