// EimEditView.cpp --- 見た目を管理するクラス
#ifndef _INC_EIMEDITVIEW
#define _INC_EIMEDITVIEW
#include <gtkmm.h>
#include <string>
#include <list>
#include "enum.hpp"
#include "EimEngine.hpp"

class EimEditView : public Gtk::Window // {{{
{
	public:

	private:
		// widgets {{{
		Gtk::VBox m_pbox; // 縦にバッファとコマンドラインを並べる
		Gtk::TextView m_buffview; // バッファの中身を表示するビュー
		Gtk::ScrolledWindow m_buffscroll; // バッファ内スクロールバー
		Gtk::Entry m_cmdline; // コマンドライン
		Gtk::Label m_stsline; // status line 現在のモード等の情報を表示する
		// }}}

		EimEngine *m_eimEngine;
		Glib::ustring m_fname;

	public:
		EimEditView();
		virtual ~EimEditView();

		void readcmd();
		void onKeyPress( GdkEventKey* );
		bool cur_move_forward();
		bool cur_move_backward();
		bool cur_move_preline();
		bool cur_move_nextline();
		bool readtext(Glib::ustring);

		// getter and setter {{{
		Mode _get_mode();
		void _set_mode(Mode);

		std::string _get_filename();
		void _set_filename(std::string);

		void _set_eimEngine(EimEngine);
		// }}}
}; // }}}

#endif //INC_EIMEDITVIEW
