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
	// 可視フレームとタイトルを持ったGtk::Frameに加える
	add( m_pbox );
	show_all_children();
	resize(400, 600); // 初期ウィンドウサイズ
	// }}}
	_set_mode(MOVE); // init mode
}

EimEditView::~EimEditView()
{
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
	}
	return true;
}

void EimEditView::editModeKeyPressEvent( GdkEventKey* event )
{
	if( event->keyval == GDK_KEY_Escape )
	{
		_set_mode( MOVE ); // move mode に移行する
		return;
	}
	// ESC key以外はバッファに入力
	Gtk::Window::on_key_press_event( event );
}
void EimEditView::moveModeKeyPressEvent( GdkEventKey* event )
{
	if( event->keyval == GDK_KEY_i )
	{
		_set_mode( EDIT );
		return;
	}
	// とりあえず、i以外のキー入力は無視する
}
void EimEditView::cmdlineModeKeyPressEvent( GdkEventKey* event )
{
	if( event->keyval == GDK_KEY_Escape )
	{
		_set_mode( MOVE );
	}
	// if( event->keyval == GDK_KP_Enter )
	// {
	// 	   m_cmdline.get_text()
	// }
	// ESC, Enter以外は無視する
	Gtk::Window::on_key_press_event( event );
}
// m_cmdline上でEnter keyを押されたらcmdlineの入力を読み取る
void EimEditView::parseCmdLine()
{
	Gtk::MessageDialog( m_cmdline.get_text() ).run();
}

// setter and getter {{{
std::string EimEditView::_get_filename() { return m_filename; }
void EimEditView::_set_filename(std::string fname) { m_filename = fname; }
Mode EimEditView::_get_mode() { return m_mode; }
void EimEditView::_set_mode(Mode mode) { m_mode = mode; }
// }}}
