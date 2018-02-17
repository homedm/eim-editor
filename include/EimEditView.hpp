// EimEditView.cpp --- 見た目を管理するクラス
#ifndef _INC_EIMEDITVIEW
#define _INC_EIMEDITVIEW
#include <gtkmm.h>
#include <string>
#include <list>
#include "enum.hpp"

class EimEditView : public Gtk::Window // {{{
{
	public:

	private:
		Gtk::VBox m_pbox; // 縦にバッファとコマンドラインを並べる
		Gtk::TextView m_buffview; // バッファの中身を表示するビュー
		Gtk::ScrolledWindow m_buffscroll; // バッファ内スクロールバー
		Gtk::Entry m_cmdline; // コマンドライン
		Mode m_mode;
		std::string m_filename;

	public:
		EimEditView();
		virtual ~EimEditView();

		void readcmd();
		bool onKeyPress( GdkEventKey* );
		void moveModeKeyPressEvent( GdkEventKey* );
		void editModeKeyPressEvent( GdkEventKey* );
		void cmdlineModeKeyPressEvent( GdkEventKey* );
		void parseCmdLine();

		// getter and setter {{{
		Mode _get_mode();
		void _set_mode(Mode);

		std::string _get_filename();
		void _set_filename(std::string);
		// }}}
}; // }}}

#endif //INC_EIMEDITVIEW
