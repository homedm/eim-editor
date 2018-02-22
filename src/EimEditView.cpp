// EimEditView.cpp ---
#include <gtkmm.h>
#include <memory>
#include <locale.h>
#include "../include/enum.hpp"
#include "../include/EimEditView.hpp"
#include "../include/EimEngine.hpp"

EimEditView::EimEditView()
{
	_set_mode(MOVE); // init mode
}

EimEditView::~EimEditView()
{
	hide();
}

void EimEditView::onKeyPress( GdkEventKey* event) // {{{
{
	// MOVEモードの時のみtrueが返ってくる
	if( m_eimEngine != 0 && m_eimEngine->procesKeyPressEvent( event )) return;

	Gtk::TextView::on_key_press_event( event );
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

// setter and getter {{{
Mode EimEditView::_get_mode() { return m_eimEngine->_get_mode(); }
void EimEditView::_set_mode(Mode mode)
{
	m_eimEngine->_set_mode( mode );
	m_sig_mode_changed.emit();
}
SIG_MODE_CHANGED EimEditView::sig_mode_changed(){ return m_sig_mode_changed; }

void EimEditView::_set_eimEngine(EimEngine *eimEngine){ m_eimEngine = eimEngine;}
// }}}
