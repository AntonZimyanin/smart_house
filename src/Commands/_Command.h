#pragma once

#include "../Utils/StringEx.h"
using namespace std;

class CContext;

class ICommand
{
public:
    ICommand(){}
    virtual ~ICommand(){}

    virtual const char* Name() = 0;
    virtual const char* Hint() = 0; // вернуть короткое описание команды
    // вернуть полное описание команды для следующего набора уточнений
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        return "Нет дополнительной информации по введённой команде\n";
    }
    // выполнить команду с переданным списком параметров
    // чтобы не дублировать лишний раз список параметров - его можно менять
    // всё равно после выполнения команды он не используется
    // returns выполнена команда или есть какие либо ошибки в наборе параметров
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters) = 0;
};

