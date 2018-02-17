#include <gtkmm.h>
#include <vector>
#include <memory>
#include "../include/enum.hpp"
#include "../include/EimEditView.hpp"

int main(int argc, char *argv[])
{
	// GTKの初期化
	Gtk::Main kit(argc, argv);

	EimEditView editview; // ウィンドウを作る

	// イベントループに入る
	Gtk::Main::run( editview );

	kit.quit();

	return 0;
}
