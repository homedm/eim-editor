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

						// make window
						WINDOW *v_active_window = newwin(LINES-3, COLS, 0, 0); //main window
						WINDOW *v_command_window = newwin(3, COLS, LINES-2, 0); // commnad line window

						BufferClass o_buffer_container[] = {
								BufferClass(v_active_window)
						};
						CommandLineClass o_command_line = CommandLineClass();
				}

		public:
				~ScreenClass()
				{
						endwin(this.window_name);
				}

				int split_window(){
						//ウィンドウを均一に横に分割する
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
						delwin(this.window_name);
				}


				// modeを返す。
				int mode?(){
						return this.mode;
				}

				// move_y, move_xだけ現在のカーソルの位置を移動させる.
				int move_cursor(int move_y, int move_x){
						wgetyx(window_name, cursor_y, cursor_x);
						wmove(window_name, cursor_y + move_y, cursor_x + move_x);
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
						endwin(this.window_name);
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
