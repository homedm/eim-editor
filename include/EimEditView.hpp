// EimEditView.cpp --- 見た目を管理するクラス
#ifndef _INC_EIMEDITVIEW
#define _INC_EIMEDITVIEW
#include <gtkmm.h>
#include <string>
#include "enum.hpp"
#include "EimEngine.hpp"

class EimEngine;

typedef sigc::signal<void> SIG_MODE_CHANGED;

class EimEditView : public Gtk::TextView // {{{
{
	private:
		SIG_MODE_CHANGED m_sig_mode_changed;
		EimEngine *m_eimEngine;

	public:
		EimEditView();
		virtual ~EimEditView();

		SIG_MODE_CHANGED sig_mode_changed();

		void onKeyPress( GdkEventKey* ); // 入力されたキーをEimEngineに渡す

		// カーソル移動
		bool cur_move_forward();
		bool cur_move_backward();
		bool cur_move_preline();
		bool cur_move_nextline();

		// getter and setter {{{
		Mode _get_mode();
		void _set_mode(Mode);

		void _set_eimEngine(EimEngine*);
		// }}}
}; // }}}

#endif //INC_EIMEDITVIEW
