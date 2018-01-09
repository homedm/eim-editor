#include <ncurses.h>
#include <locale.h>

enum KINDWINDOW
{
		COMMANDWINDOW,
		BUFFERWINDOW
};
enum Mode
{
		MOVEMODE,
		EDITMODE,
		COMMANDMODE,
		VISUALMODE,
};

// 他のウィンドウを管理するクラス
class ScreenClass
{
		public:
				ScreenClass()
				{
						initscr();
						WINDOW *v_active_window, v_command_window;

						// make window
						*v_active_window = newwin(LINES-3, COLS, 0, 0); //main window
						*v_command_window = newwin(2, COLS, LINES-1, 0); // commnad line window

						BufferClass o_buffer_window[] = {
								BufferClass(v_active_window, BUFFERWINDOW)
						};
						CommandLineClass o_command_line = CommandLineClass();
				}

		public:
				~ScreenClass()
				{
						endwin(window_name);
				}
}
// 個々のbufferについて管理するクラス
class BufferClass
{
		// construter
		public:
				BufferClass(WINDOW *window_name)
				{
						Mode mode = MOVEMODE;

						wclear(window_name); //画面表示
						cbreak();

						setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
						start_color();

						//キー入力された文字を表示しないモードにする。初めはmove modeのため。
						noecho();
				}

		public:
				~BufferClass()
				{
						// ScreenClassのo_buffer_windowからも消す処理を追加する.
						delwin(window_name);
				}


				// modeを返す。
				int check_mode(){
						return mode;
				}

};

// command line についてのクラス
Class CommandLineClass
{
		public:
				CommandLineClass(WINDOW *window_name)
				{
						wclear(window_name); // clear window
						setlocale();
				}
		public:
				~CommandLineClass()
				{
						endwin(window_name);
				}
};

int main(int argc, char *argv[])
{
		// main loop
		while (true)
		{
				getch(); //キー入力
		}

		return 0;
}
