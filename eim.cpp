#include <ncurses.h>
#include <locale.h>

#define MOVEMODE 0
#define EDITMODE 1
#define COMMANDMODE 2
#define VISUALMODE 3

class WindowClass
{
		// construter
		public:
				WindowClass()
				{
						// windowの作成 {{{
						// }}}
						clear(); //画面表示
						cbreak();

						setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
						start_color();

						//キー入力された文字を表示しないモードにする。初めはmove modeのため。
						noecho();
				}

				// modeを返す。
				int check_mode(){
				}

};
int init_app()
{
		initscr();
}
int finish_app()
{
		endwin();
}
int main(int argc, char *argv[])
{

		init_app();
		WindowClass window();

		// main loop
		while (true)
		{
				getch(); //キー入力
		}

		return 0;
}
