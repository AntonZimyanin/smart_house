#pragma once
#include "_Command.h"

class CCmdVolume : public ICommand
{
public:
    CCmdVolume(){}

    virtual const char* Name()
    {
        return "volume";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Узнать или задать уровень громкости воспроизведения";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "volume\n"
                   "volume <уровень громкости 0-128>\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

