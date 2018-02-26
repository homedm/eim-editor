// EimCmdLine.cpp --- command line class
#include <gtkmm.h>
#include <glibmm.h>
#include "../include/enum.hpp"
#include "../include/EimEngine.hpp"
#include "../include/EimCmdLine.hpp"

EimCmdLine::EimCmdLine()
{
}

EimCmdLine::EimCmdLine()
{
}

// Cmd modeでのキー入力イベントをハンドルする
bool EimCmdLine::on_key_press_event( GdkEventKey * key_event )
{
	if( m_eimEngine != 0 && m_eimEngine->procesKeyPressEvent( key_event )) return true;

	// CMD Mode
	if( _get_mode() == CMD ) base::on_key_press_event(key_event);
	return true;
}
void EimCmdLine::on_key_press_enter()
{
	Glib::ustring cmd = get_text();
	// add history
	m_cmdhistory.push_back(cmd);
	m_eimEngine->parseCmdLine(cmd);
	set_text("");
}
void EimCmdLine::_set_mode(Mode){ m_eimEngine->_set_mode(Mode); }
Mode EimCmdLine::_get_mode(){ return m_eimEngine->_get_mode(); }
void EimCmdLine::_set_eimEngine(EimCmdLine* eimEngine) { m_eimEngine = eimEngine; }
