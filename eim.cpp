#include <curses.h>
#include <ncurses.h>
#include <locale.h>

enum KINDWINDOW // {{{
{
		COMMANDWINDOW,
		BUFFERWINDOW
}; // }}}
enum Mode // {{{
{
		MOVEMODE,
		EDITMODE,
		COMMANDMODE,
		VISUALMODE,
}; // }}}
// 個々のbufferについて管理するクラス
class BufferClass // {{{
{
		private:
				Mode mode;
				WINDOW *window_id;
		// construter
		public:
				BufferClass(WINDOW *window_name)
				{
						mode = MOVEMODE;
						window_id = window_name;

						wclear(window_id); //画面表示
						cbreak();

						start_color();

						//キー入力された文字を表示しないモードにする。初めはmove modeのため。
						noecho();
				}

		public:
				~BufferClass()
				{
						// ScreenClassのo_buffer_windowからも消す処理を追加する.
						delwin(this -> window_id);
				}


				// getter
				const Mode& _mode() const{
						return this -> mode;
				}
				// setter
				void _mode(Mode setmode) {
						this -> mode = setmode;
				}

				// move_y, move_xだけ現在のカーソルの位置を移動させる.
				int move_cursor(int move_y, int move_x){
						int cursor_y, cursor_x;
						getmaxyx(this->window_id, cursor_y, cursor_x);
						wmove(this->window_id, cursor_y + move_y, cursor_x + move_x);
				}

				int command_branch(int key)
				{
						switch (key) {
								case 'h':
										// move left
										move_cursor(0, -1); break;
								case 'j':
										//move down
										move_cursor(1, 0); break;
								case 'k':
										// move up
										move_cursor(-1, 0); break;
								case 'l': 
										// move right
										move_cursor(0, 1); break;
						}
				}

}; // }}}

// command line についてのクラス
class CommandLineClass // {{{
{
		private:
				WINDOW *window_id;
		public:
				CommandLineClass(WINDOW *window_name)
				{
						window_id = window_name;
						wclear(window_id); // clear window
				}
		public:
				~CommandLineClass()
				{
						delwin(this->window_id);
				}
}; // }}}

// 他のウィンドウを管理するクラス
class ScreenClass // {{{
{
		private:
				WINDOW *v_command_window;
				BufferClass* o_buffer_container[10];
				CommandLineClass* o_command_line;
				int o_active_buffer_number;

		public:
				ScreenClass()
				{
						setlocale(LC_ALL, ""); //マルチバイト文字列を有効にする
						initscr();

						// make window
						// commnad line window
						v_command_window = newwin(3, COLS, LINES-2, 0);
						//buffer windwo
						o_buffer_container[0](newwin(LINES-3, COLS, 0, 0));
						o_command_line = CommandLineClass();
						o_active_buffer_number = 0;
				}

		public:
				~ScreenClass()
				{
						endwin(); //ncurses終了
				}

				int split_window(){
						//ウィンドウを均一に横に分割する
				}

				int command_branch(int key)
				{
						switch (key) {
								case ':': 
										// change command mode
										this.o_command_line.command_branch(); break;
								default: 
										this.o_buffer_container[o_active_buffer_number].command_branch(key); break;
						}
				}
}; // }}}


int main(int argc, char *argv[])
{
		ScreenClass screen;
		int key;
		// main loop
		while (true)
		{
				key = getch(); //キー入力
				ScreenClass.command_branch(key);
		}

		return 0;
}
