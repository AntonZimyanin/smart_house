#pragma once
#include "_Command.h"

class CCmdLoad : public ICommand
{
public:
    CCmdLoad(){}

    virtual const char* Name()
    {
        return "load";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Загрузить из указанного файла расположение объектов";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "load txt <filename> - загрузить текстовый файл\n"
                   "load bin <filename> - загрузить бинарный файл\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

