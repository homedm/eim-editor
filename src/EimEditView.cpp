// EimEngineClass.cpp ---
#include <gtkmm.h>
#include <memory>
#include <locale.h>
#include "../include/enum.hpp"
#include "../include/EimEditView.hpp"

EimEditView::EimEditView()
{
	// make window gui {{{
	m_buffview.get_buffer()->set_text( "hello world" );
	m_buffview.set_monospace(true); // modify font width

	// キー入力イベントを書き換える
	set_events(Gdk::KEY_PRESS_MASK);
	this->signal_key_press_event().connect(
			sigc::mem_fun( *this, &EimEditView::onKeyPress), false);

	// スクロールバーを設定
	m_buffscroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_buffscroll.add( m_buffview );

	m_cmdline.set_text(" コマンドライン ");
	m_cmdline.signal_activate().connect(
			sigc::mem_fun( *this, &EimEditView::parseCmdLine));

	// boxに追加する
	m_pbox.pack_start( m_buffscroll );
	m_pbox.pack_end( m_cmdline, false, false, 0 );
	m_pbox.pack_end( m_stsline, false, false, 0 );
	// 可視フレームとタイトルを持ったGtk::Frameに加える
	add( m_pbox );
	show_all_children();
	resize(400, 600); // 初期ウィンドウサイズ
	// }}}
	_set_mode(MOVE); // init mode
	m_stsline.set_text( "Move Mode" );
}

EimEditView::~EimEditView()
{
	hide();
}

// key event {{{
bool EimEditView::onKeyPress( GdkEventKey* event)
{
	// モードによって処理を分ける
	switch( _get_mode() )
	{
		case MOVE:
			moveModeKeyPressEvent( event ); // move mode process
			break;
		case EDIT:
			editModeKeyPressEvent( event ); // edit mode process
			break;
		case CMD:
			cmdlineModeKeyPressEvent( event ); // cmd line mode process
			break;
	}
	return true;
}

void EimEditView::editModeKeyPressEvent( GdkEventKey* event )
{
	guint key = event->keyval;
	if( key == GDK_KEY_Escape )
	{
		_set_mode( MOVE ); // move mode に移行する
		m_stsline.set_text( "Move Mode" );
		return;
	}
	if( key == GDK_KEY_colon
			&& event->state == Gdk::CONTROL_MASK )
	{
		_set_mode( CMD );
		m_stsline.set_text( "CmdLine Mode" );
		m_cmdline.grab_focus();
		return;
	}
	// ESC key以外はバッファに入力
	Gtk::Window::on_key_press_event( event );
}
void EimEditView::moveModeKeyPressEvent( GdkEventKey* event )
{
	guint key = event->keyval;
	if( key == GDK_KEY_i)
	{
		_set_mode( EDIT );
		m_stsline.set_text( "Edit Mode" );
		return;
	}
	if( key == GDK_KEY_colon
			&& event->state == Gdk::CONTROL_MASK )
	{
		_set_mode( CMD );
		m_stsline.set_text( "CmdLine Mode" );
		m_cmdline.grab_focus();
		return;
	}
	// the smallest movement {{{
	if( key == GDK_KEY_h)
	{
		// to go left
		cur_move_backward();
	}
	if( key == GDK_KEY_j )
	{
		// to go down
		cur_move_nextline();
	}
	if( key == GDK_KEY_k )
	{
		// to go up
		cur_move_preline();
	}
	if( key == GDK_KEY_l )
	{
		// to go right
		cur_move_forward();
	}
	//}}}
}

bool EimEditView::cur_move_forward()
{
	Gtk::TextIter iter = m_buffview.get_buffer()->get_insert()->get_iter();
	iter.forward_char();
	m_buffview.get_buffer()->place_cursor(iter);
	return true;
}

bool EimEditView::cur_move_backward()
{
	Gtk::TextIter iter = m_buffview.get_buffer()->get_insert()->get_iter();
	iter.backward_char();
	m_buffview.get_buffer()->place_cursor(iter);
	return true;
}
// 一つ上の行の先頭に移動する
bool EimEditView::cur_move_preline()
{
	Gtk::TextIter iter = m_buffview.get_buffer()->get_insert()->get_iter();
	// 前の行の先頭に移動
	iter.backward_line();

	// ここで実際にカーソルが移動する
	m_buffview.get_buffer()->place_cursor(iter);
	return true;
}

//次の行の先頭に移動
bool EimEditView::cur_move_nextline()
{
	Gtk::TextIter iter = m_buffview.get_buffer()->get_insert()->get_iter();
	iter.forward_line();

	// ここで実際にカーソルが移動する
	m_buffview.get_buffer()->place_cursor(iter);
	return true;
}

void EimEditView::cmdlineModeKeyPressEvent( GdkEventKey* event )
{
	if( event->keyval == GDK_KEY_Escape )
	{
		_set_mode( MOVE );
		m_stsline.set_text( "Move Mode" );
		m_buffview.grab_focus(); // return focus to buffview
	}
	// ESC, Enter以外は無視する
	Gtk::Window::on_key_press_event( event );
}

// m_cmdline上でEnter keyを押されたらcmdlineの入力を読み取る
void EimEditView::parseCmdLine()
{
	Glib::ustring cmd = m_cmdline.get_text();
	if( cmd == "q" ) hide();
}

bool EimEditView::readtext( Glib::ustring fname )
{
	return true;
}

// setter and getter {{{
std::string EimEditView::_get_filename() { return m_filename; }
void EimEditView::_set_filename(std::string fname) { m_filename = fname; }
Mode EimEditView::_get_mode() { return m_mode; }
void EimEditView::_set_mode(Mode mode) { m_mode = mode; }
// }}}
