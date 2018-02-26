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
		Glib::ustring m_fname;
		typedef Gtk::TextView base;

	protected:
		virtual bool on_key_press_event( GdkEventKey* event); // 入力されたキーをEimEngineに渡す

	public:
		EimEditView();
		virtual ~EimEditView();

		// カーソル移動
		bool cur_move_forward();
		bool cur_move_backward();
		bool cur_move_preline();
		bool cur_move_nextline();
		void scroll_adjust( double within_margin=0.05 );

		// delete
		void backspace_one_char();

		// file
		bool read_file( Glib::ustring );
		bool write_file( Glib::ustring );
		bool write_file();
		// getter and setter {{{
		Mode _get_mode();
		void _set_mode(Mode);

		void _set_eimEngine(EimEngine*);

		Glib::ustring _get_fname();
		void _set_fname(Glib::ustring);
		// }}}
}; // }}}

#endif //INC_EIMEDITVIEW
