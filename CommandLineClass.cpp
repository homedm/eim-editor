#include "CommandLineClass.h"
#include <ncurses.h>
#include "enum.h"

CommandLineClass::CommandLineClass(WINDOW *window_name)
{
		window_id = window_name;
		wclear(window_id); // clear window
}

CommandLineClass::~CommandLineClass()
{
		delwin(this->window_id);
}

