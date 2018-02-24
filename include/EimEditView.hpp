// EimEditView.cpp --- 見た目を管理するクラス
#ifndef _INC_EIMEDITVIEW
#define _INC_EIMEDITVIEW
#include <gtkmm.h>
#include <string>
#include "enum.hpp"
#include "EimEngine.hpp"

class EimEngine;

class EimEditView : public Gtk::TextView // {{{
{
	private:
		EimEngine *m_eimEngine;
		typedef Gtk::TextView base;

	public:
		EimEditView();
		virtual ~EimEditView();

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

	protected:
		virtual bool on_key_press_event( GdkEventKey* event); // 入力されたキーをEimEngineに渡す
}; // }}}

#endif //INC_EIMEDITVIEW
