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
	add_events(Gdk::KEY_PRESS_MASK);
	signal_key_press_event().connect(
			sigc::mem_fun( *this, &EimEditView::onKeyPress ) );

	m_cmdline.set_text(" コマンドライン ");
	// シグナルとスロットをコネクト
	m_cmdline.signal_activate().connect(
			sigc::mem_fun( *this, &EimEditView::readcmd ) );

	m_buffscroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_buffscroll.add( m_buffview );
	m_pbox.pack_start( m_buffscroll );
	m_pbox.pack_end( m_cmdline, false, false, 0 );
	add( m_pbox );
	show_all_children();
	resize(400, 600);
	// }}}
	_set_mode(MOVE); // init mode
}

EimEditView::~EimEditView()
{
}

// key event {{{
bool EimEditView::onKeyPress( GdkEventKey* event)
{
	Gtk::MessageDialog( m_buffview.get_buffer()->get_text() ).run();
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
void EimEditView::readcmd()
{
	Gtk::MessageDialog( m_cmdline.get_text() ).run();
}

// setter and getter {{{
std::string EimEditView::_get_filename() { return m_filename; }
void EimEditView::_set_filename(std::string fname) { m_filename = fname; }
Mode EimEditView::_get_mode() { return m_mode; }
void EimEditView::_set_mode(Mode mode) { m_mode = mode; }
// }}}
