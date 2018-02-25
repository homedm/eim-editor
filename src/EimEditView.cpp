// EimEditView.cpp ---
#include <gtkmm.h>
#include <memory>
#include <locale.h>
#include "../include/enum.hpp"
#include "../include/EimEditView.hpp"
#include "../include/EimEngine.hpp"

EimEditView::EimEditView()
{
}

EimEditView::~EimEditView()
{
}

bool EimEditView::on_key_press_event( GdkEventKey * key_event ) // {{{
{
	// MOVE, CMD Modeの時のみtrueが返ってくる
	if( m_eimEngine != 0 && m_eimEngine->procesKeyPressEvent( key_event )) return true;

	// EDIT Modeの時のみ実行される
	base::on_key_press_event( key_event );
	return true;
} // }}}


// ### move command methods {{{
bool EimEditView::cur_move_forward()
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	iter.forward_char();
	get_buffer()->place_cursor(iter);
	return true;
}

bool EimEditView::cur_move_backward()
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	iter.backward_char();
	get_buffer()->place_cursor(iter);
	return true;
}
// 一つ上の行の先頭に移動する
bool EimEditView::cur_move_preline()
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	// 前の行の先頭に移動
	iter.backward_line();

	// ここで実際にカーソルが移動する
	get_buffer()->place_cursor(iter);
	return true;
}

//次の行の先頭に移動
bool EimEditView::cur_move_nextline()
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	iter.forward_line();

	// ここで実際にカーソルが移動する
	get_buffer()->place_cursor(iter);
	return true;
}
// }}}

// file
bool EimEditView::read_file( Glib::ustring filename )
{
	_set_fname(filename);

	Glib::RefPtr <Glib::IOChannel> refChannel;
	Glib::ustring filebuf;

	try {
		refChannel = Glib::IOChannel::create_from_file( _get_fname(), "r" );
		Glib::ustring linebuf;
		while ( refChannel->read_line(linebuf) == Glib::IO_STATUS_NORMAL ) filebuf += linebuf;
	} catch ( const Glib::Exception &e ) {
		Gtk::MessageDialog( "Failed open the file:" + _get_fname() ).run();
	}

	get_buffer()->set_text(filebuf);
	return true;
}

// setter and getter {{{
Mode EimEditView::_get_mode() { return m_eimEngine->_get_mode(); }
void EimEditView::_set_mode(Mode mode) { m_eimEngine->_set_mode( mode ); }

void EimEditView::_set_eimEngine(EimEngine *eimEngine){ m_eimEngine = eimEngine;}

Glib::ustring EimEditView::_get_fname() { return m_fname; }
void EimEditView::_set_fname( Glib::ustring filename ){ m_fname = filename; }
// }}}
