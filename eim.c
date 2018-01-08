#include <ncurses.h>

int main(int argc, char *argv[])
{
		initscr(); //端末制御の開始

		erase(); //画面表示

		move(10, 20);
		addstr("Hello World");
		getch(); //キー入力

		endwin(); //端末制御の終了
		return 0;
}
