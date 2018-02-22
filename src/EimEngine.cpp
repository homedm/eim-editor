// EimEngine.cpp --- ユーザ入力コマンドを処理する
#include <gtkmm.h>
#include <memory>
#include "../include/EimEditView.hpp"
#include "../include/enum.hpp"
#include "../include/EimEngine.hpp"

EimEngine::EimEngine()
{
}
EimEngine::~EimEngine()
{
}

bool EimEngine::procesKeyPressEvent( GdkEventKey* event )
{
	// モードによって処理を分ける
	switch( _get_mode() )
	{
		case MOVE:
			return moveModeKeyPressEvent( event ); // move mode process
		case EDIT:
			return editModeKeyPressEvent( event ); // edit mode process
		case CMD:
			return cmdlineModeKeyPressEvent( event ); // cmd line mode process
	}
}

bool EimEngine::editModeKeyPressEvent( GdkEventKey* event ) // {{{
{
	guint key = event->keyval;
	if( key == GDK_KEY_Escape )
	{
		_set_mode( MOVE ); // move mode に移行する
	}
	if( key == GDK_KEY_colon
			&& event->state == Gdk::CONTROL_MASK )
	{
		_set_mode( CMD );
	}
	return true;
} // }}}

bool EimEngine::moveModeKeyPressEvent( GdkEventKey* event ) // {{{
{
	guint key = event->keyval;
	if( key == GDK_KEY_i)
	{
		_set_mode( EDIT );
	}
	if( key == GDK_KEY_colon
			&& event->state == Gdk::CONTROL_MASK )
	{
		_set_mode( CMD );
	}
	// the smallest movement {{{
	if( key == GDK_KEY_h)
	{
		// to go left
		m_editor->cur_move_backward();
	}
	if( key == GDK_KEY_j )
	{
		// to go down
		m_editor->cur_move_nextline();
	}
	if( key == GDK_KEY_k )
	{
		// to go up
		m_editor->cur_move_preline();
	}
	if( key == GDK_KEY_l )
	{
		// to go right
		m_editor->cur_move_forward();
	}
	//}}}
	return false;
} // }}}

bool EimEngine::cmdlineModeKeyPressEvent( GdkEventKey* event ) // {{{
{
	if( event->keyval == GDK_KEY_Escape )
	{
		_set_mode( MOVE );
		m_editor->grab_focus(); // return focus to buffview
	}
	return false;
} // }}}

// m_cmdline上でEnter keyを押されたらcmdlineの入力を読み取る
void EimEngine::parseCmdLine() // {{{
{
	Glib::ustring cmd = m_cmdline->get_text();
	if( cmd == "q" ) hide();
} // }}}

void EimEngine::readcmd()
{
}

// setter and getter {{{
void EimEngine::_set_mode( Mode mode ) { m_mode = mode; }
Mode EimEngine::_get_mode() { return m_mode; }
void EimEngine::_set_eimEditView( EimEditView* view ) { m_editor = view;}
EimEditView* EimEngine::_get_eimEditView(){ return m_editor; }
void EimEngine::_set_cmdline( Gtk::Entry* cmdline ){ m_cmdline = cmdline; }
// }}}
