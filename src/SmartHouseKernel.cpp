// SmartHouseKernel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// #include <conio.h>
#include "Context.h"
#include "Utils/StringEx.h"
#include "Storage/BinLoader.h"
#include "Storage/BinStorer.h"
#include "SmartObjects/RoomObject.h"
#include "Commands/_Command.h"
using namespace std;

int main(void)
{
    CContext context;
    {// ограничиваем зону существования объекта loader
        CBinLoader loader("myroom.bin");
        // Костыль: в глубине библиотеки SDL при запуске мелодии на воспроизведение может выдаваться ошибка
        // отобразим её красным, на воспроизведение она не влияет
        // учитывая что CModel не должен ничего выдавать на экран при воспроизведении (поскольку не взаимодействует с консолью, а только возвращает ошибку),
        // то изменение цвета выводимого текста тут будет влиять только на вывод ошибки в SDL
        context.m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        bool bOk = context.m_ActiveModel.Load(&loader, &context.m_ObjFactory);
        context.m_Console.SetTextColor(); // цвет текста по умолчанию
        if (!bOk)
        { // загрузка не удалась - создаём схему по умолчанию
            context.m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
            context.m_Console << "Не удалось загрузить предыдущую схему объектов" << endl;
            context.m_Console.SetTextColor(); // цвета консоли по умолчанию
            ICommand* pCmd = context.m_Commands.FindCommand("demo");
            if (pCmd)
            {
                vector<stringEx> dummy;
                pCmd->Execute(&context, dummy);
            }
        }
    }
    context.m_Console << "Введите команду (например, help)" << endl;
    while (!context.IsExiting())
    {
        context.m_ActiveModel.DrawAll(context.m_Console);
        if (!context.m_Console.SetConsolePos(context.m_Console.CommandLogOutputPos()))
            return false;
        if (!context.m_Console.SetTextColor()) // use default output color
            return false;
        context.m_Console << "> "; // приглашение ввести следующую команду
        stringEx cmd;
        getline(context.m_Console, OUT cmd);
        vector<stringEx> vWords = cmd.Split(" ", true);
        if (!vWords.size())
            continue;
        // Обработка введённой команды
        ICommand* pCmd = context.m_Commands.FindCommand(vWords[0].c_str());
        if (!pCmd)
        {
            context.m_Console << "Неизвестная команда" << endl;
            continue;
        }
        vWords.erase(vWords.begin());
        pCmd->Execute(&context, vWords);
    }
    CBinStorer storer("myroom.bin");
    if (!context.m_ActiveModel.Store(&storer))
    {
        context.m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        context.m_Console << "Внимание: не удалось сохранить конфигурацию объектов в файл" << endl;
        context.m_Console.SetTextColor(); // цвета консоли по умолчанию
        getchar();
    }
    return 0;
}





