// EimEditView.cpp --- 見た目を管理するクラス
#ifndef _INC_MAINWINDOW
#define _INC_MAINWINDOW
#include <gtkmm.h>
#include <string>
#include "enum.hpp"
#include "EimEngine.hpp"
#include "EimEditView.hpp"

class MainWindow : public Gtk::Window // {{{
{
	public:
		MainWindow();
		virtual ~MainWindow();

		void onModeChanged(); // モードが変化したときに呼ばれる

	private:
		// widgets {{{
		EimEditView *m_editor; // buffer
		Gtk::VBox m_pbox; // 縦にバッファとコマンドラインを並べる
		Gtk::ScrolledWindow m_buffscroll; // バッファ内スクロールバー
		Gtk::Entry m_cmdline; // コマンドライン
		Gtk::Label m_stsline; // status line 現在のモード等の情報を表示する

		EimEngine *m_eimEngine;
		// }}}
}; // }}}

#endif //INC_MAINWINDOW
