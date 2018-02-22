// EimEngine.cpp --- ユーザ入力コマンドを処理する
#include <gtkmm.h>
#include <memory>
#include "../include/EimEditView.hpp"
#include "../include/enum.hpp"
#include "../include/EimEngine.hpp"

void EimEngine::EimEngine()
{
}
void EimEngine::~EimEngine()
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
		m_eimEditView->m_stsline.set_text( "Move Mode" );
	}
	if( key == GDK_KEY_colon
			&& event->state == Gdk::CONTROL_MASK )
	{
		_set_mode( CMD );
		m_eimEditView->m_stsline.set_text( "CmdLine Mode" );
		m_eimEditView->m_cmdline.grab_focus();
	}
	return true;
} // }}}

bool EimEngine::moveModeKeyPressEvent( GdkEventKey* event ) // {{{
{
	guint key = event->keyval;
	if( key == GDK_KEY_i)
	{
		_set_mode( EDIT );
		m_eimEditView->m_stsline.set_text( "Edit Mode" );
	}
	if( key == GDK_KEY_colon
			&& event->state == Gdk::CONTROL_MASK )
	{
		_set_mode( CMD );
		m_eimEditView->m_stsline.set_text( "CmdLine Mode" );
		m_eimEditView->m_cmdline.grab_focus();
	}
	// the smallest movement {{{
	if( key == GDK_KEY_h)
	{
		// to go left
		m_eimEditView->cur_move_backward();
	}
	if( key == GDK_KEY_j )
	{
		// to go down
		m_eimEditView->cur_move_nextline();
	}
	if( key == GDK_KEY_k )
	{
		// to go up
		m_eimEditView->cur_move_preline();
	}
	if( key == GDK_KEY_l )
	{
		// to go right
		m_eimEditView->cur_move_forward();
	}
	//}}}
	return false;
} // }}}

bool EimEngine::cmdlineModeKeyPressEvent( GdkEventKey* event ) // {{{
{
	if( event->keyval == GDK_KEY_Escape )
	{
		_set_mode( MOVE );
		m_eimEditView->m_stsline.set_text( "Move Mode" );
		m_eimEditView->m_buffview.grab_focus(); // return focus to buffview
	}
	return false;
} // }}}

// m_cmdline上でEnter keyを押されたらcmdlineの入力を読み取る
void EimEditView::parseCmdLine() // {{{
{
	Glib::ustring cmd = m_cmdline.get_text();
	if( cmd == "q" ) hide();
} // }}}

// setter and getter {{{
void EimEngine::_set_mode(Mode) { m_mode = mode; }
Mode EimEngine::_get_mode() { return m_mode; }
void EimEngine::_set_eimEditView( EimEditView* view ) { m_eimEditView = view;}
EimEditView* EimEngine::_get_eimEditView(){ return *m_eimEditView;}
// }}}
