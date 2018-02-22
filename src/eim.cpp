#include <gtkmm.h>
#include <vector>
#include <memory>
#include "../include/enum.hpp"
#include "../include/EimEditView.hpp"
#include "../include/EimEngine.hpp"
#include "../include/MainWindow.hpp"

int main(int argc, char *argv[])
{
	// GTKの初期化
	Gtk::Main kit(argc, argv);

	MainWindow win; // ウィンドウを作る

	// イベントループに入る
	Gtk::Main::run( win );

	kit.quit();

	return 0;
}
