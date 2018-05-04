// EimEditView.hpp --- 見た目を管理するクラス
#ifndef _INC_EIMEDITVIEW
#define _INC_EIMEDITVIEW
#include <gtkmm.h>
#include <glibmm.h>
#include <string>
#include "enum.hpp"

class EimEngine;
class EimCmdLine;

class EimEditView : public Gtk::TextView // {{{
{
	private:
		EimEngine *m_eimEngine;
		Glib::ustring m_fname;
		typedef Gtk::TextView base;

	protected:
		virtual bool on_key_press_event( GdkEventKey* ); // 入力されたキーをEimEngineに渡す
		virtual bool on_button_press_event( GdkEventButton* );

	public:
		EimEditView();
		virtual ~EimEditView();

		void scroll_adjust( double within_margin=0.05 );

		// カーソル移動
		bool cur_move_forward();
		bool cur_move_backward();
		bool cur_move_preline();
		bool cur_move_nextline();
		bool cur_move_forward_word_start();
		bool cur_move_backward_word_start();

		bool cur_move_top();
		bool cur_move_end();
		// }}}

		// delete commands {{{
		void backspace_one_char();
		void delete_one_char();
		// }}}

		// file IO
		bool read_file( Glib::ustring );
		bool write_file( Glib::ustring );
		bool write_file();

		// getter and setter {{{
		Mode _get_mode();
		void _set_mode(Mode);

		void _set_eimEngine(EimEngine*);
		EimEngine* _get_eimEngine(void);

		Glib::ustring _get_fname();
		void _set_fname(Glib::ustring);
		// }}}
}; // }}}
#endif //INC_EIMEDITVIEW
