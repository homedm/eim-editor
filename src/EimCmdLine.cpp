// EimCmdLine.cpp --- command line class
#include <gtkmm.h>
#include <glibmm.h>
#include "../include/enum.hpp"
#include "../include/EimCmdLine.hpp"
#include "../include/EimEngine.hpp"

EimCmdLine::EimCmdLine()
{
	push_history("");
}

EimCmdLine::~EimCmdLine()
{
}

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
	push_history(cmd);
	m_eimEngine->parseCmdLine(cmd);
	set_text("");
}

void EimCmdLine::set_iter() { m_iter = m_cmdhistory.begin(); }
void EimCmdLine::backward_iter(){
	if( m_iter != m_cmdhistory.begin() ){ --m_iter; }
}
void EimCmdLine::forward_iter(){
	if( m_iter != --( m_cmdhistory.end() ) ){ ++m_iter; }
}

void EimCmdLine::show_pre_cmdhist()
{
	backward_iter();
	set_text(*m_iter);
}

void EimCmdLine::show_next_cmdhist()
{
	forward_iter();
	set_text(*m_iter);
}

// 頭に追加していく
void EimCmdLine::push_history(Glib::ustring cmd)
{
	m_cmdhistory.push_front(cmd);
}

void EimCmdLine::_set_mode(Mode mode){ m_eimEngine->_set_mode(mode); }
Mode EimCmdLine::_get_mode(){ return m_eimEngine->_get_mode(); }
void EimCmdLine::_set_eimEngine(EimEngine* eimEngine) { m_eimEngine = eimEngine; }
