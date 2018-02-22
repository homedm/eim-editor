// EimEngine.hpp ---　コマンドを処理するクラス
#ifndef _INC_EIMENGINE
#define _INC_EIMENGINE
#include <gtkmm.h>
#include <memory>
#include "enum.hpp"
#include "EimEditView.hpp"

class EimEditView;

// 編集操作はEimEditViewのメソッドを直接コールする
class EimEngine : public Gtk::Widget
{
	private:
		Mode m_mode;
		EimEditView *m_editor;
		Gtk::Entry *m_cmdline;

		bool editModeKeyPressEvent( GdkEventKey* );
		bool cmdlineModeKeyPressEvent( GdkEventKey*);
		bool moveModeKeyPressEvent( GdkEventKey* );

		void readcmd();

	public:
		EimEngine();
		~EimEngine();

		bool procesKeyPressEvent( GdkEventKey* );

		void parseCmdLine();

		// setter and getter
		void _set_mode( Mode );
		Mode _get_mode();
		void _set_eimEditView( EimEditView* );
		EimEditView* _get_eimEditView();
		void _set_cmdline( Gtk::Entry* );
};
#endif // INC_EIMENGINE
