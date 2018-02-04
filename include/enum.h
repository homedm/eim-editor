#ifndef _INC_ENUM
#define _INC_ENUM
// key code {{{
#define EXITPROGRAM 0
#define KEY_ESC 27
// }}}
enum KINDWINDOW // {{{
{
		COMMANDWINDOW,
		BUFFERWINDOW
}; // }}}
enum Mode // {{{
{
		MOVEMODE,
		EDITMODE,
		COMMANDMODE,
		VISUALMODE,
}; // }}}
#endif //INCENUM
