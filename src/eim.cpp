#include <gtkmm.h>
#include <vector>
#include <memory>
#include "../include/enum.hpp"
#include "../include/EimEditView.hpp"

int main(int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);

	EimEditView editview;
	Gtk::Main::run( editview );

	return 0;
}
