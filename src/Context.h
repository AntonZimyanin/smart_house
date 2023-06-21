#pragma once
#include "Commands/_CommandHolder.h"
#include "SmartObjects/_ObjectFactory.h"
#include "Utils\ConsoleManip.h"
#include "Model.h"

class CContext
{
private:
	// флаг, что пора завершить работу программы
	// для завершения работы просто выставить в true
    bool m_bExiting;
public:
    CContext();
    virtual ~CContext();

	CModel m_ActiveModel; // текущая схема расположения датчиков
    CConsoleManip m_Console; // консоль, с возможностью изменения цвета и положения вывода текста 
    CObjectFactory m_ObjFactory; 
    CCommandHolder m_Commands; // набор доступных консольных команд
    void Exit()
    {
        m_bExiting = true;
    }
    bool IsExiting() const
    {
        return m_bExiting;
    }
};

