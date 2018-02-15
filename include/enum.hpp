#ifndef _INC_ENUM
#define _INC_ENUM
// key code {{{
#define KEY_ESC 27
#define EXITPROGRAM 2
#define SUCCESS 1
#define ERROR 0
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
