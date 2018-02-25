// EimEngine.cpp --- ユーザ入力コマンドを処理する
#include <gtkmm.h>
#include <memory>
#include "../include/EimEditView.hpp"
#include "../include/enum.hpp"
#include "../include/EimEngine.hpp"

EimEngine::EimEngine()
{
	_set_mode(MOVE); // init mode
}
EimEngine::~EimEngine()
{
}

SIG_MODE_CHANGED EimEngine::sig_mode_changed() { return m_sig_mode_changed; }

bool EimEngine::procesKeyPressEvent( GdkEventKey* event )
{
	// モードによって処理を分ける
	switch( _get_mode() )
	{
		case MOVE:
			moveModeKeyPressEvent( event ); // move mode process
			return true;
		case CMD:
			m_editor->get_buffer()->backspace(
					m_editor->get_buffer()->get_insert()->get_iter()
					);
			cmdlineModeKeyPressEvent( event ); // cmd line mode process
			return true;
		case EDIT:
			editModeKeyPressEvent( event ); // edit mode process
			return false;
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
	}
	return false;
} // }}}

// m_cmdline上でEnter keyを押されたらcmdlineの入力を読み取る
void EimEngine::parseCmdLine() // {{{
{
	// 入力されたコマンドを取得する
	Glib::ustring cmd_text = m_cmdline->get_text();
	m_cmdline->set_text("");

	std::vector<Glib::ustring> cmd;
	Glib::ustring sep = " ";
	for(int i = 0, n; i <= cmd_text.length(); i=n+1){
		n = cmd_text.find_first_of( sep, i );
		if( n == Glib::ustring::npos ){ n = cmd_text.length(); }
		Glib::ustring tmp = cmd_text.substr( i, n-i );
		cmd.push_back(tmp);
	}

	if( cmd[0].compare("q") == 0 ) // compareは等しいとき0を返す
	{
		exit(0);
	}
	if( cmd[0].compare("e") == 0 )
	{
		m_editor->read_file(cmd[1]);
	}

	_set_mode(MOVE);
} // }}}

// setter and getter {{{
void EimEngine::_set_mode( Mode mode ) {
	m_mode = mode;
	m_sig_mode_changed.emit();
}
Mode EimEngine::_get_mode() { return m_mode; }
void EimEngine::_set_eimEditView( EimEditView* view ) { m_editor = view;}
EimEditView* EimEngine::_get_eimEditView(){ return m_editor; }
void EimEngine::_set_cmdline( Gtk::Entry* cmdline ){ m_cmdline = cmdline; }
// }}}
