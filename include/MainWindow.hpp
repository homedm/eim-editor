// MainWindow.cpp --- 見た目を管理するクラス
#ifndef _INC_MAINWINDOW
#define _INC_MAINWINDOW
#include <gtkmm.h>
#include <string>
#include "enum.hpp"

class EimEditView;
class EimCmdLine;
class EimEngine;

class MainWindow : public Gtk::Window // {{{
{
	public:
		MainWindow();
		virtual ~MainWindow();

		void onModeChanged(); // モードが変化したときに呼ばれる

	protected:
		virtual bool on_button_press_event( GdkEventButton* event );

	private:
		// widgets {{{
		EimEditView *m_editor; // buffer
		Gtk::VBox m_pbox; // 縦にバッファとコマンドラインを並べる
		Gtk::ScrolledWindow m_buffscroll; // バッファ内スクロールバー
		EimCmdLine *m_cmdline;
		Gtk::Label m_stsline; // status line 現在のモード等の情報を表示する

		EimEngine *m_eimEngine;
		typedef Gtk::Window base;
		// }}}
}; // }}}

#endif //INC_MAINWINDOW
