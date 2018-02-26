// EimEngine.hpp ---　コマンドを処理するクラス
#ifndef _INC_EIMENGINE
#define _INC_EIMENGINE
#include <gtkmm.h>
#include <memory>
#include "enum.hpp"

class MainWindow;
class EimEditView;
class EimCmdLine;

typedef sigc::signal<void> SIG_MODE_CHANGED;

// 編集操作はEimEditViewのメソッドを直接コールする
class EimEngine : public Gtk::Widget
{
	private:
		Mode m_mode;
		EimEditView *m_editor;
		EimCmdLine *m_cmdline;
		SIG_MODE_CHANGED m_sig_mode_changed;

		bool editModeKeyPressEvent( GdkEventKey* );
		bool cmdlineModeKeyPressEvent( GdkEventKey*);
		bool moveModeKeyPressEvent( GdkEventKey* );

	public:
		EimEngine();
		~EimEngine();

		bool procesKeyPressEvent( GdkEventKey* );
		void parseCmdLine(Glib::ustring);
		SIG_MODE_CHANGED sig_mode_changed();

		// setter and getter
		void _set_mode( Mode );
		Mode _get_mode();
		void _set_eimEditView( EimEditView* );
		EimEditView* _get_eimEditView();
		void _set_cmdline( EimCmdLine* );
};
#endif // INC_EIMENGINE
