#include <gtkmm.h>
#include <memory>
#include "enum.hpp"
#include "EimEditView.hpp"

//、編集操作はEimEditViewのメソッドを直接コールする
class EimEngine : public Gtk::Widget
{
	public:
		bool procesKeyPressEvent( GdkEventKey* );
		// setter and getter
		void _set_mode( Mode );
		Mode _get_mode();
		void _set_eimEditView( EimEditView*);
		EimEditView* _get_eimEditView();

	private:
		EimEditView *m_eimEditView; // カレントEimEditViewオブジェクトへのポインタ
		Mode m_mode;
		bool editModeKeyPressEvent( GdkEventKey*);
		bool cmdlineModeKeyPressEvent( GdkEventKey*);
		bool moveModeKeyPressEvent( GdkEventKey* );
		void parseCmdLine();
}
