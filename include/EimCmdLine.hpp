// EimCmdLine.hpp --- コマンドラインでの処理を担当する
#ifdef _INC_EIMCMDLINE
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
		void _set_mode(Mode);
		Mode _get_mode();

	protected:
		virtual bool on_key_press_event( GdkEventKey* );

	public:
		EimCmdLine();
		virtual ~EimCmdLine();

		void on_key_press_enter();

		void _set_eimEngine(EimEngine*);
};
#endif // INC_EIMENGINE
