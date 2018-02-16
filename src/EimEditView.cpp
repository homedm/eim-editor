// EimEngineClass.cpp --- commandline, buffer縺ｫ蟇ｾ縺吶ｋ謫堺ｽ懊ｒ陦後≧
#include <gtkmm.h>
#include <memory>
#include <locale.h>
#include "../include/enum.hpp"
#include "../include/EimEditView.hpp"

EimEditView::EimEditView()
{
	buffview.get_buffer()->set_text( "hello world" );
	cmdline.set_text(" コマンドライン ");
	// シグナルとスロットをコネクト
	cmdline.signal_activate().connect(
			sigc::mem_fun( *this, &EimEditView::readcmd ) );

	buffscroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	buffscroll.add( buffview );
	pbox.pack_start( buffscroll );
	pbox.pack_end( cmdline, false, false, 0 );
	add( pbox );
	show_all_children();
	resize(600, 800);
}

EimEditView::~EimEditView()
{
}

// エンターが入力されたら呼び出される。
// コマンドラインビューの内容を読み込む
// スロット関数
void EimEditView::readcmd()
{
	Gtk::MessageDialog( cmdline.get_text() ).run();
}

std::string EimEditView::_get_filename()
{
}

void EimEditView::_set_filename(std::string fname)
{
}
