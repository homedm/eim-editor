// EimCmdLine.hpp --- コマンドラインでの処理を担当する
#ifndef _INC_EIMCMDLINE
#define _INC_EIMCMDLINE
#include <gtkmm.h>
#include <glibmm.h>
#include <list>
#include "enum.hpp"

class EimEngine;

class EimCmdLine : public Gtk::Entry
{
	private:
		EimEngine *m_eimEngine;
		std::list<Glib::ustring> m_cmdhistory;
		std::list<Glib::ustring>::iterator m_iter;
		void push_history(Glib::ustring);
		void forward_iter();
		void backward_iter();

		void _set_mode(Mode);
		Mode _get_mode(void);
		typedef Gtk::Entry base;

	protected:
		virtual bool on_key_press_event( GdkEventKey* );
		virtual bool on_button_press_event( GdkEventButton* );

	public:
		EimCmdLine();
		virtual ~EimCmdLine();

		void on_key_press_enter();
		void show_pre_cmdhist();
		void show_next_cmdhist();
		void set_iter(); // no setter

		void _set_eimEngine(EimEngine*);
		EimEngine* _get_eimEngine(void);
};
#endif // INC_EIMENGINE
