#include <ncurses.h>
#include <locale.h>
#include <vector>
#include <memory>
#include "../include/enum.hpp"
#include "../include/BufferClass.hpp"
#include "../include/CommandLineClass.hpp"
#include "../include/EimEngineClass.hpp"

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
	initscr();
	cbreak();
	//キー入力された文字を表示しないモードにする。初めはmove modeのため。
	noecho();
	keypad(stdscr, TRUE);

	// set color {{{
	if(has_colors()){
		start_color();
		// init_pair(number, foreground, background);
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_BLACK, COLOR_WHITE);
		init_pair(3, COLOR_GREEN, COLOR_RED);
	}
	// }}}
	curs_set(1);

	// eimEinginインスタンスを作成する
	EimEngineClass *eimEngine = new EimEngineClass();

	refresh();

	int key; // 入力キーを保持するための変数

	// main loop
	while (true)
	{
		key = getch(); //キー入力
		if( eimEngine->command_branch(key) == EXITPROGRAM) break;
	}

	delete eimEngine;

	endwin();
	std::system("reset");
	printf("finished editing\n");
	exit(0);
	return 0;
}
