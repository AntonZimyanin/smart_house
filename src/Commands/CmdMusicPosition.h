#pragma once
#include "_Command.h"

class CCmdMusicPosition : public ICommand
{
public:
    CCmdMusicPosition(){}

    virtual const char* Name()
    {
        return "musicposition";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Узнать или установить текущую позицию проигрывания музыки";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "musicposition\n"
                   "musicposition <позиция проигрывания в секундах>\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

