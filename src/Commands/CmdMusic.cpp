#include "../stdafx.h"
#include "CmdMusic.h"
#include <iostream>
#include "../Context.h"
using namespace std;

std::string CCmdMusic::Help(CContext* pContext, const vector<stringEx>& vParameters)
{
    if (!vParameters.size())
        return "использование:\n"
               "music play\n"
               "music stop\n"
               "music next\n"
               "music rewind\n"
               "music reload\n"
               "music list\n";
    if (vParameters.size() == 1)
    {
        stringEx par(vParameters[0]);
        par.strlwr(); // сравниваем параметры без учёта регистра
        if (par == "play")
            return "Включить воспроизведение музыкального файла.\n"
                   "использование:\n"
                   "music play\n";
        if (par == "stop")
            return "Выключить воспроизведение музыкального файла.\n"
                   "использование:\n"
                   "music stop\n";
        if (par == "next")
            return "Перейти к воспроизведению следующего музыкального файла.\n"
                   "использование:\n"
                   "music next\n";
        if (par == "rewind")
            return "Начать воспроизведение текущего файла с начала.\n"
                   "использование:\n"
                   "music rewind\n";
        if (par == "reload")
            return "Перечитать список музыкальных файлов с диска.\n"
                   "использование:\n"
                   "music reload\n";
        if (par == "list")
            return "Вывести список доступных музыкальных файлов.\n"
                   "использование:\n"
                   "music list\n";
    }
    return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
}

bool CCmdMusic::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0)
    {
        // если параметры не указаны - отобразим подсказку
        Help(pContext, vector<stringEx>());
        return false;
    }
    stringEx par(vParameters[0]);
    par.strlwr(); // сравниваем параметры без учёта регистра
    if (par == "play")
    {
        // при запуске проигрывания музыки выводится ошибка (где-то в исходниках SDL)
        // выведем её красным, если она будет
        pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        pContext->m_ActiveModel.m_MusicContext.Play();
        return true;
    }
    if (par == "stop")
    {
        pContext->m_ActiveModel.m_MusicContext.Stop();
        return true;
    }
    if (par == "next")
    {
        if (!pContext->m_ActiveModel.m_MusicContext.SelectNextFile())
        {
            pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red); // выведем ошибку красным
            pContext->m_Console << "Ошибка при попытке воспроизвести файл" << endl;
            return false;
        }
        return true;
    }
    if (par == "rewind")
    {
        pContext->m_ActiveModel.m_MusicContext.Position(0);
        return true;
    }
    if (par == "reload")
    {
        pContext->m_ActiveModel.m_MusicContext.ReloadMusicList();
        pContext->m_ActiveModel.m_MusicContext.PrintAvailableMusics(pContext->m_Console);
        return true;
    }
    if (par == "list")
    {
        pContext->m_ActiveModel.m_MusicContext.PrintAvailableMusics(pContext->m_Console);
        return true;
    }

    // указан недопустимый параметр команды
    pContext->m_Console << "Неподдерживаемый параметр команды" << endl;
    return false;
}