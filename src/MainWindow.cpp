#include <gtkmm.h>
#include "../include/EimEditView.hpp"
#include "../include/EimEngine.hpp"
#include "../include/enum.hpp"
#include "../include/MainWindow.hpp"

MainWindow::MainWindow()
{
	m_editor = new EimEditView;
	m_eimEngine = new EimEngine;

	m_editor->_set_eimEngine( m_eimEngine );
	m_eimEngine->_set_eimEditView( m_editor );

	// make window gui {{{
	m_editor->set_monospace(true); // modify font width

	// スクロールバーを設定
	m_buffscroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_buffscroll.add( *m_editor );

	m_cmdline.set_text(" コマンドライン ");

	// boxに追加する
	m_pbox.pack_start( m_buffscroll );
	m_pbox.pack_end( m_cmdline, false, false, 0 );
	m_pbox.pack_end( m_stsline, false, false, 0 );

	// 可視フレームとタイトルを持ったGtk::Frameに加える
	add( m_pbox );
	show_all_children();
	resize(400, 600); // 初期ウィンドウサイズ
	// }}}

	// キー入力イベントを書き換える
	set_events(Gdk::KEY_PRESS_MASK);

	// signal_key_press_event().connect(
		// 	sigc::mem_fun( m_editor, &EimEditView::onKeyPress) );

	m_cmdline.signal_activate().connect(
			sigc::mem_fun( m_eimEngine, &EimEngine::parseCmdLine));

	m_editor->sig_mode_changed().connect(
			sigc::mem_fun( *this, &MainWindow::onModeChanged) );

}

MainWindow::~MainWindow()
{
}

// モードが変化したときに呼ばれる ハンドラ
void MainWindow::onModeChanged()
{
	Glib::ustring text;
	switch( m_editor->_get_mode() ){
		case CMD:
			text = "CMD";
			m_stsline.grab_focus();
			break;
		case EDIT:
			text = "EDIT";
			m_editor->grab_focus();
			break;
		case MOVE:
			text = "MOVE";
			m_editor->grab_focus();
			break;
	}

	m_stsline.set_text(text);
}
