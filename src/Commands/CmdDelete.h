#pragma once
#include "_Command.h"

class CCmdDelete : public ICommand
{
public:
    CCmdDelete(){}

    virtual const char* Name()
    {
        return "delete";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Удалить существующий объект";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters);
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);    
};

