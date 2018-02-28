// EimEngine.cpp --- ユーザ入力コマンドを処理する
#include <gtkmm.h>
#include <memory>
#include "../include/enum.hpp"
#include "../include/EimEditView.hpp"
#include "../include/EimCmdLine.hpp"
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
			cmdlineModeKeyPressEvent( event ); // cmd line mode process
			return false;
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
		return true;
	}
	if( key == GDK_KEY_colon
			&& event->state == Gdk::CONTROL_MASK )
	{ _set_mode( CMD ); }
	// the smallest movement {{{
	if( key == GDK_KEY_h) { m_editor->cur_move_backward(); }
	if( key == GDK_KEY_j ) { m_editor->cur_move_nextline(); }
	if( key == GDK_KEY_k ) { m_editor->cur_move_preline(); }
	if( key == GDK_KEY_l ) { m_editor->cur_move_forward(); }
	//}}}
	// word movement {{{
	if( key == GDK_KEY_w ) { m_editor->cur_move_forward_word_start(); }
	if( key == GDK_KEY_b ) { m_editor->cur_move_backward_word_start(); }
	// }}}
	// buffer movement {{{
	if( key == GDK_KEY_t ) { m_editor->cur_move_top(); }
	if( key == GDK_KEY_e ) { m_editor->cur_move_end(); }
	// }}}

	m_editor->scroll_adjust();
	// delete commands {{{
	if( key == GDK_KEY_x ) { m_editor->backspace_one_char(); }
	if( key == GDK_KEY_d ) { m_editor->delete_one_char(); }
	return true;
} // }}}

bool EimEngine::cmdlineModeKeyPressEvent( GdkEventKey* event ) // {{{
{
	guint key = event->keyval;
	if( key == GDK_KEY_Escape )
	{
		m_cmdline->set_text(""); // clear text in cmd line
		_set_mode( MOVE );
	}
	if( key == GDK_KEY_p
			&& event->state == Gdk::CONTROL_MASK )
	{
		m_cmdline->show_pre_cmdhist();
	}
	if( key == GDK_KEY_n
			&& event->state == Gdk::CONTROL_MASK )
	{
		m_cmdline->show_next_cmdhist();
	}
	return false;
} // }}}

// m_cmdline上でEnter keyを押されたらcmdlineの入力を読み取る
void EimEngine::parseCmdLine(Glib::ustring cmd_text) // {{{
{
	std::vector<Glib::ustring> cmd;
	Glib::ustring sep = " ";
	for(int i = 0, n; i <= cmd_text.length(); i=n+1){
		n = cmd_text.find_first_of( sep, i );
		if( n == Glib::ustring::npos ){ n = cmd_text.length(); }
		Glib::ustring tmp = cmd_text.substr( i, n-i );
		cmd.push_back(tmp);
	}

	if( cmd[0].compare("q") == 0 ) { exit(0); }
	if( cmd[0].compare("e") == 0 ) { m_editor->read_file(cmd[1]); }
	if( cmd[0].compare("w") == 0 )
	{
		if( cmd[1].length() > 0 ){ m_editor->write_file(cmd[1]); }
		else { m_editor->write_file(); }
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
void EimEngine::_set_cmdline( EimCmdLine* cmdline ){ m_cmdline = cmdline; }
// }}}
