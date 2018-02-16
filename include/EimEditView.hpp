// EimEditView.cpp --- 見た目を管理するクラス
#ifndef _INC_EIMEDITVIEW
#define _INC_EIMEDITVIEW
#include <gtkmm.h>
#include <string>
#include <list>
#include "enum.hpp"

class EimEditView : public Gtk::Window // {{{
{
	private:
		Gtk::VBox pbox; // 縦にバッファとコマンドラインを並べる
		Gtk::TextView buffview; // バッファの中身を表示するビュー
		Gtk::ScrolledWindow buffscroll; // バッファ内スクロールバー
		Gtk::Entry cmdline; // コマンドライン

	public:
		EimEditView();
		virtual ~EimEditView();

		void readcmd();

		// getter and setter {{{
		std::string _get_filename();
		void _set_filename(std::string);
		// }}}
}; // }}}

#endif //INC_EIMEDITVIEW
