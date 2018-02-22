// EimEditView.cpp ---
#include <gtkmm.h>
#include <memory>
#include <locale.h>
#include "../include/enum.hpp"
#include "../include/EimEditView.hpp"
#include "../include/EimEngine.hpp"

EimEditView::EimEditView()
{
	// make window gui {{{
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
	m_eimEngine->_set_eimEditView(this*);
}

EimEditView::~EimEditView()
{
	hide();
}

void EimEditView::onKeyPress( GdkEventKey* event) // {{{
{
	// MOVEモードの時のみtrueが返ってくる
	if( m_eimEngine != 0 && m_eimEngine->procesKeyPressEvent( event ) return;

	Gtk::Window::on_key_press_event( event );
} // }}}


// ### move command methods {{{
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
// }}}

bool EimEditView::readtext( Glib::ustring fname )
{
	std::ifstream ifs(fname);
	return true;
}

// setter and getter {{{
std::string EimEditView::_get_filename() { return m_filename; }
void EimEditView::_set_filename(std::string fname) { m_filename = fname; }
Mode EimEditView::_get_mode() { return m_eimEngine->m_mode; }
void EimEditView::_set_mode(Mode mode) { m_eimEngine->_get_mode( mode ); }
void EimEditView::_set_eimEngine(EimEngine *eimEngine){ m_eimEngine = eimEngine;}
// }}}
