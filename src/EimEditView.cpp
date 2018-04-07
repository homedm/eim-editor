// EimEditView.cpp --- Buffer class
#include <gtkmm.h>
#include <memory>
#include "../include/enum.hpp"
#include "../include/EimEngine.hpp"
#include "../include/EimEditView.hpp"

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
	// キー入力がそのまま入力される
	if( _get_mode() == EDIT ) base::on_key_press_event( key_event );
	return true;
} // }}}


// ### move command methods ### {{{
bool EimEditView::cur_move_forward()
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	if( iter.forward_char() )
	{
		get_buffer()->place_cursor(iter);
		return true;
	}
	return false;
}

bool EimEditView::cur_move_backward()
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	iter.backward_char();
	get_buffer()->place_cursor(iter);
	return true;
}

bool EimEditView::cur_move_forward_word_start()
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	// 次の単語の先頭に移動するメソッドが内ので
	iter.forward_word_end();
	iter.forward_word_end();
	iter.backward_word_start();
	get_buffer()->place_cursor(iter);
	return true;
}

bool EimEditView::cur_move_backward_word_start()
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	iter.backward_word_start();
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

bool EimEditView::cur_move_top()
{
	Gtk::TextIter iter = get_buffer()->begin();
	get_buffer()->place_cursor(iter);
	return true;
}
bool EimEditView::cur_move_end()
{
	Gtk::TextIter iter = get_buffer()->end();
	get_buffer()->place_cursor(iter);
	return true;
}

// カーソルが画面外に出ないようにスクロールして調節する
void EimEditView::scroll_adjust( double within_margin )
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	scroll_to(iter, within_margin);
	return;
}
// }}}

// ### delete command methods ### {{{
void EimEditView::backspace_one_char()
{
	Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
	// delete left character on cursor
	get_buffer()->backspace( iter );
	return;
}
void EimEditView::delete_one_char()
{
	// delete right character on cursor
	if( cur_move_forward() )
	{
		Gtk::TextIter iter = get_buffer()->get_insert()->get_iter();
		get_buffer()->backspace( iter );
	}
}
// }}}

// ### file ###  {{{
bool EimEditView::read_file( Glib::ustring filename )
{
	_set_fname(filename);

	Glib::RefPtr <Glib::IOChannel> refChannel;
	Glib::ustring filebuf;

	try {
		refChannel = Glib::IOChannel::create_from_file( _get_fname(), "r" );
		Glib::ustring linebuf;
		while ( refChannel->read_line(linebuf) == Glib::IO_STATUS_NORMAL ) filebuf += linebuf;
		// show text file
		get_buffer()->set_text(filebuf);

		Gtk::TextIter iter = get_buffer()->begin();
		get_buffer()->place_cursor(iter);
	} catch ( const Glib::Exception &e ) {
		Gtk::MessageDialog( "Failed open the file:" + _get_fname() ).run();
	}

	return true;
}

bool EimEditView::write_file( Glib::ustring filename )
{
	_set_fname( filename );

	Glib::RefPtr <Glib::IOChannel> refChannel;

	try {
		refChannel = Glib::IOChannel::create_from_file( _get_fname(), "w" );
		Glib::ustring filebuf = get_buffer()->get_text( get_buffer()->begin(), get_buffer()->end() );
		refChannel->write( filebuf );
	} catch ( const Glib::Exception &e ) {
		Gtk::MessageDialog( "Failed open the file:" + _get_fname() ).run();
		return false;
	}
	return true;
}

bool EimEditView::write_file()
{
	// fnameがセットされているか
	if( _get_fname().length() <= 0 )
	{
		Gtk::MessageDialog( "Not yet set target file" ).run();
		return false;
	}
	Glib::RefPtr <Glib::IOChannel> refChannel;

	try {
		refChannel = Glib::IOChannel::create_from_file( _get_fname(), "w" );
		Glib::ustring filebuf = get_buffer()->get_text( get_buffer()->begin(), get_buffer()->end() );
		refChannel->write( filebuf );
	} catch ( const Glib::Exception &e ) {
		Gtk::MessageDialog( "Failed open the file:" + _get_fname() ).run();
		return false;
	}
	return true;
}
// }}}

bool EimEditView::on_button_press_event( GdkEventButton* event )
{
	m_eimEngine->returnfocus();
	return true;
}

// setter and getter  {{{
Mode EimEditView::_get_mode() { return m_eimEngine->_get_mode(); }
void EimEditView::_set_mode(Mode mode) { m_eimEngine->_set_mode( mode ); }

void EimEditView::_set_eimEngine(EimEngine *eimEngine){ m_eimEngine = eimEngine;}
EimEngine* EimEditView::_get_eimEngine(){ return m_eimEngine; }

Glib::ustring EimEditView::_get_fname() { return m_fname; }
void EimEditView::_set_fname( Glib::ustring filename ){ m_fname = filename; }
// }}}
